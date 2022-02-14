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
			// remote.waitForSignal();
			// auto tempRemoteData = remote.getPacketData();
			// quadControls.input(tempRemoteData.thrust, tempRemoteData.yaw, tempRemoteData.pitch, tempRemoteData.roll);
			started = true;
		}
		void loop() {
			// remoteData = remote.getPacketData();
			// sleep_ms(10);
		}
	} // namespace Core0

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	namespace Core1 {
		DEBUG_RUN(auto last = get_absolute_time();)

		void rateControl();
		void angleControl();

		auto defaultPins = Pico::SPI::Pins();
		auto mpu9250 = Mpu9250::create(spi1, std::move(defaultPins));

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void setup() {
			Misc::Blink::setup();
		}

		void loop() {
			if (!started) {
				Misc::Blink::run(70);

			} else {
				Misc::Blink::run(250);
				mpu9250.checkSettings();
				mpu9250.checkMpuVals();
				sleep_ms(50);
				Misc::clearConsole();
			}
		}

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void rateControl() {}

		void angleControl() {}
	} // namespace Core1
} // namespace Application
