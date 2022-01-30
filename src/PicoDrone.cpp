#include "pico/stdlib.h"
#include "hardware/i2c.h"

#include <iostream>
#include <array>
#include <stdlib.h>

#include "Helpers/Pico.hpp"
#include "Helpers/Misc.hpp"
#include "Helpers/Macros.hpp"

#include "PwmDevices/MotorESC.hpp"
#include "Quad.hpp"
#include "Remote.hpp"
#include "MPU9250.hpp"

namespace Application {
	using namespace PicoPilot;

	bool started = false;
	int16_t thrustData = 0;
	Pico::SPI::Pins pins;

	auto mpu9250 = Mpu9250::create(spi1, std::move(pins), 100);
	auto quadControls = Quad::Controls::create({6, 7, 8, 9});
	auto remote = Remote::create();

	namespace Core0 {
		void setup() {
			remote.waitForSignal();
			started = true;
		}
		void loop() {
			thrustData = remote.getPacketData().data;
		}
	} // namespace Core0

	namespace Core1 {
		void setup() {
			Misc::Blink::setup();
		}
		void loop() {
			Misc::Blink::start();

			if (started) {
				int16_t thrust = thrustData;
				int16_t yaw = 511;
				int16_t pitch = 511;
				int16_t roll = 511;

				quadControls.input(std::move(thrust), std::move(yaw), std::move(pitch), std::move(roll));
				// quadControls.debugPrint();
				mpu9250.debugPrint();

				sleep_ms(100);
				Misc::clearConsole();
			}
		}
	} // namespace Core1

} // namespace Application
