#include "pico/stdlib.h"
#include "hardware/clocks.h"

#include "Drone.hpp"
#include "Helpers/Pico.hpp"
#include "Helpers/Misc.hpp"
#include "Helpers/Macros.hpp"
#include "Pid.hpp"

namespace Application {
	using namespace PicoPilot;

	const float centerOffset = 511.f;
	bool started = false;
	auto remoteData = Remote::Packet();
	auto quadControls = Quad::Controls::create({6, 7, 8, 9});

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// The remote stuff was separated from the other process is due to it being slow.
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
			sleep_ms(10);
		}
	} // namespace Core0

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	namespace Core1 {
		DEBUG_RUN(auto last = get_absolute_time();)

		auto defaultPins = Pico::SPI::Pins();
		auto mpu9250 = Mpu9250::create(spi1, std::move(defaultPins), 100);

		Pid::Configs pitchPidConfig = {0.f, 0.0f, 0.f, -600.f, 600.f, -200.f, 200.f};
		Pid::Configs rollPidConfig = {0.f, 0.0f, 0.f, -600.f, 600.f, -200.f, 200.f};
		Pid::Configs yawPidConfig = {3.f, 0.15f, 0.f, -600.f, 600.f, -200.f, 200.f};
		auto pitchPid = Pid::create(pitchPidConfig);
		auto rollPid = Pid::create(rollPidConfig);
		auto yawPid = Pid::create(yawPidConfig);

		void setup() {
			Misc::Blink::setup();
		}
		void loop() {
			if (!started) {
				Misc::Blink::start(70);

			} else {
				Misc::Blink::start(250);

				auto feedback = mpu9250.gyroVals();
				int16_t pitch = pitchPid.step(0, -feedback.Y) + 511;
				int16_t roll = rollPid.step(0, -feedback.X) + 511;
				int16_t yaw = yawPid.step(0, -feedback.Z) + 511;

				quadControls.input(remoteData.thrust, yaw, pitch, roll);

				DEBUG_RUN({
					// remoteData.debugPrint();
					// mpu9250.debugPrint();
					quadControls.debugPrint();

					printf("Controller output: Pitch = %d, Roll = %d\n\n", pitch, roll);
					printf("Loop time = %lld microseconds\n", absolute_time_diff_us(last, get_absolute_time()));

					sleep_ms(70);
					Misc::clearConsole();
					last = get_absolute_time();
				})
			}
		}
	} // namespace Core1
} // namespace Application
