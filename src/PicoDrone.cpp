#include "pico/stdlib.h"

#include <iostream>
#include <stdlib.h>

#include "Helpers/Pico.hpp"
#include "Helpers/Arduino.hpp"
#include "Helpers/Misc.hpp"
#include "PwmDevices/Servo.hpp"
#include "PwmDevices/MotorESC.hpp"

namespace Application {
	using namespace LocalLib::Helpers::Pico;
	using namespace LocalLib::Helpers;
	using namespace LocalLib;

	namespace Core0 {
		AnalogReader pot0 = AnalogReader::create(27);
		PwmDevices::MotorESC test0 = PwmDevices::MotorESC::create(4);

		void setup() {}
		void loop() {
			test0.setLevel(pot0.read());
		}
	} // namespace Core0

	namespace Core1 {
		const uint led = PICO_DEFAULT_LED_PIN;
		bool toggle = 0;

		void setup() {
			gpio_init(led);
			gpio_set_dir(led, true);
		}
		void loop() {
			if (Misc::interval(250)) {
				toggle ^= 1UL << 0;
				gpio_put(led, toggle);
			}
		}
	} // namespace Core1

} // namespace Application
