#include "pico/stdlib.h"
#include "hardware/i2c.h"

#include <iostream>
#include <array>
#include <stdlib.h>

#include "Helpers/Pico.hpp"
#include "Helpers/Misc.hpp"
#include "Helpers/Macros.hpp"
#include "PwmDevices/PwmDevices.hpp"
#include "I2C/Comms.hpp"
#include "I2C/MPU6050.hpp"
#include "Quad.hpp"

namespace Application {
	using namespace LocalLib::Helpers;
	using namespace LocalLib;

	namespace Core0 {
		Pico::AnalogReader thrust = Pico::AnalogReader::create(26);
		Pico::AnalogReader yaw = Pico::AnalogReader::create(27);
		Pico::AnalogReader pitch = Pico::AnalogReader::create(28);

		Quad::Controls testQuad = Quad::Controls::create({4, 5, 6, 7});

		void setup() {}
		void loop() {
			testQuad.input(thrust.read(), yaw.read(), pitch.read(), (uint16_t)0);

			DEBUG_RUN(std::cout << '\n';)
		}
	} // namespace Core0

	namespace Core1 {
		void setup() {
			Misc::Blink::setup();
		}
		void loop() {
			Misc::Blink::start();
		}
	} // namespace Core1

} // namespace Application
