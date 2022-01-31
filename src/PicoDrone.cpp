#include "pico/stdlib.h"
#include "hardware/i2c.h"

#include <array>
#include <stdlib.h>

#include "Helpers/Pico.hpp"
#include "Helpers/Misc.hpp"
#include "Helpers/Macros.hpp"

#include "PwmDevices/MotorESC.hpp"
#include "Quad.hpp"
#include "Remote.hpp"
#include "MPU9250.hpp"
#include "Pid.hpp"

namespace Application {
	using namespace PicoPilot;

	bool started = false;
	auto remoteData = Remote::Packet();
	auto defaultPins = Pico::SPI::Pins();
	auto defaultConfigs = Pid::Configs();

	auto mpu9250 = Mpu9250::create(spi1, std::move(defaultPins), 100);
	auto pitchPid = Pid::create(std::move(defaultConfigs));
	auto quadControls = Quad::Controls::create({6, 7, 8, 9});
	auto remote = Remote::create();

	namespace Core0 {
		void setup() {
			remote.waitForSignal();
			started = true;
		}
		void loop() {
			remoteData = remote.getPacketData();
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
				Misc::Blink::start(250);
				int16_t thrust = remoteData.thrust;
				int16_t yaw = 115;
				int16_t pitch = 115;
				int16_t roll = 115;

				quadControls.input(std::move(thrust), std::move(yaw), std::move(pitch), std::move(roll));
				quadControls.debugPrint();
				mpu9250.debugPrint();

				sleep_ms(100);
				Misc::clearConsole();
			}
		}
	} // namespace Core1

} // namespace Application
