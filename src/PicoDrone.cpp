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

	auto quadControls = Quad::Controls::create({6, 7, 8, 9});

	const float centerOffset = 511.f;
	bool started = false;
	auto controllerData = Remote::Packet();
	auto mtx = Pico::Mutex::Mutex::create();

	namespace Core0 {
		DEBUG_RUN(auto last = get_absolute_time();)

		auto defaultPins = Pico::SPI::Pins();

		auto mpu9250 = Mpu9250::create(spi1, std::move(defaultPins), 100);
		auto remote = Remote::create();
		auto remoteData = Remote::Packet();
		auto feedback = Mpu9250::Rotation();
		int16_t setpoint = 0;

		FastPID pitchPid(1.5f, 0.f, 20.f, clock_get_hz(clk_sys) / 10, 16, true);
		FastPID rollPid(2.5f, 0.f, 20.f, clock_get_hz(clk_sys) / 10, 16, true);

		void setup() {
			remote.waitForSignal();
			auto tempRemoteData = remote.getPacketData();
			quadControls.input(tempRemoteData.thrust, tempRemoteData.yaw, tempRemoteData.pitch, tempRemoteData.roll);
			started = true;
		}
		void loop() {
			mtx.lock();

			remoteData = remote.getPacketData();
			feedback = mpu9250.filteredAngles(0.95, 0.95);

			setpoint = ((remoteData.pitch - centerOffset) / centerOffset) * 45.f;

			controllerData.pitch = pitchPid.step(-setpoint, -feedback.pitch) + 511;
			controllerData.roll = rollPid.step(-setpoint, -feedback.roll) + 511;
			controllerData.thrust = remoteData.thrust;
			controllerData.yaw = remoteData.yaw;

			DEBUG_RUN({
				mpu9250.debugPrint();
				// remote.debugPrint();
				// printf("core 0 (Hz): %f\n", 1 / ((float)absolute_time_diff_us(last, get_absolute_time()) / 1000000.f));
				sleep_ms(50);
				Misc::clearConsole();
				last = get_absolute_time();
			})

			mtx.unlock();
		}
	} // namespace Core0

	namespace Core1 {

		void setup() {
			Misc::Blink::setup();
		}
		void loop() {
			if (!started) {
				Misc::Blink::start(70);

			} else {
				mtx.lock();
				int16_t thrust = controllerData.thrust;
				int16_t yaw = controllerData.yaw;
				int16_t pitch = controllerData.pitch;
				int16_t roll = controllerData.roll;
				mtx.unlock();

				quadControls.input(std::move(thrust), std::move(yaw), std::move(pitch), std::move(roll));
				Misc::Blink::start(250);
			}
		}
	} // namespace Core1

} // namespace Application
