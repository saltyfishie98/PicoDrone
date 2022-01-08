#include "pico/stdlib.h"
#include "hardware/i2c.h"

#include <iostream>
#include <array>
#include <stdlib.h>

#include "Helpers/Pico.hpp"
#include "Helpers/Misc.hpp"
#include "Helpers/Macros.hpp"
#include "PwmDevices/PwmDevices.hpp"
#include "Quad.hpp"

namespace Application {
	using namespace LocalLib;

	Quad::Controls testQuad = Quad::Controls::create({10, 11, 12, 13});
	Pico::AnalogReader thrust = Pico::AnalogReader::create(26);
	Pico::AnalogReader yaw = Pico::AnalogReader::create(27);
	Pico::AnalogReader pitch = Pico::AnalogReader::create(28);

	namespace Core0 {
		void setup() {}
		void loop() {
			testQuad.input(thrust.read(), yaw.read(), pitch.read(), (uint16_t)0);
		}
	} // namespace Core0

	namespace Core1 {
		void setup() {
			Misc::Blink::setup();
		}
		void loop() {
			Misc::Blink::start();

			thrust.debugPrint();
			yaw.debugPrint();
			pitch.debugPrint();

			testQuad.debugPrint();
			sleep_ms(100);
			printf("\033[2J");
		}
	} // namespace Core1

} // namespace Application
