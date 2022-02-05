#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "hardware/clocks.h"

#include <array>
#include <stdlib.h>

#include "FastPID.h"

#include "Helpers/Pico.hpp"
#include "Helpers/Misc.hpp"
#include "Helpers/Macros.hpp"
#include "PwmDevices/MotorESC.hpp"
#include "Quad.hpp"
#include "Remote.hpp"
#include "MPU9250.hpp"

namespace Application {
	using namespace PicoPilot;

	const float centerOffset = 511.f;
	bool started = false;
	auto remoteData = Remote::Packet();

	auto quadControls = Quad::Controls::create({6, 7, 8, 9});

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	namespace Core0 {
		auto remote = Remote::create();

		void setup() {
			remote.waitForSignal();
			auto tempRemoteData = remote.getPacketData();
			quadControls.input(tempRemoteData.thrust, tempRemoteData.yaw, tempRemoteData.pitch, tempRemoteData.roll);
			started = true;
		}
		void loop() {
			remoteData = remote.getPacketData();
		}
	} // namespace Core0

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	namespace Core1 {
		DEBUG_RUN(auto last = get_absolute_time();)
		int16_t setpoint = 0;

		auto defaultPins = Pico::SPI::Pins();
		auto mpu9250 = Mpu9250::create(spi1, std::move(defaultPins), 100);

		FastPID pitchPid(2.3f, 0.0f, 100000.0f, clock_get_hz(clk_sys) / 10, 16, true);
		FastPID rollPid(2.3f, 0.0f, 100000.0f, clock_get_hz(clk_sys) / 10, 16, true);

		void setup() {
			Misc::Blink::setup();
		}
		void loop() {
			if (started) {
				Misc::Blink::start(70);

			} else {
				Misc::Blink::start(250);

				auto feedback = mpu9250.calibratedGyro();
				int16_t pitch = pitchPid.step(0, -feedback.Y) + 511;
				int16_t roll = rollPid.step(0, -feedback.X) + 511;

				quadControls.input(remoteData.thrust, remoteData.yaw, pitch, roll);

				DEBUG_RUN({
					mpu9250.debugPrint();

					printf("Controller output: Pitch = %d, Roll = %d\n\n", pitch, roll);
					printf("Loop time = %lld microseconds\n", absolute_time_diff_us(last, get_absolute_time()));

					sleep_ms(50);
					Misc::clearConsole();
					last = get_absolute_time();
				})
			}
		}
	} // namespace Core1

} // namespace Application
