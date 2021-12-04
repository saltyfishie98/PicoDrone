#include "pico/stdlib.h"

#include <iostream>
#include <stdlib.h>

#include "Helpers/Pico.hpp"
#include "Helpers/Misc.hpp"
#include "Quad.hpp"

namespace Application {
	using namespace LocalLib::Helpers::Pico;
	using namespace LocalLib::Helpers;
	using namespace LocalLib;

	namespace Core0 {
		AnalogReader pot0 = AnalogReader::create(27);
		Quad::SpeedControls quad0 = Quad::SpeedControls::create({4, 5, 6, 7});
		Quad::MotorSpeedCfg speedConfig = 0;

		void setup() {}
		void loop() {
			Quad::configureMotorSpeed(&speedConfig, Quad::Motor::MOTOR_0, pot0.read());
			Quad::configureMotorSpeed(&speedConfig, Quad::Motor::MOTOR_1, pot0.read());
			Quad::configureMotorSpeed(&speedConfig, Quad::Motor::MOTOR_2, pot0.read());
			Quad::configureMotorSpeed(&speedConfig, Quad::Motor::MOTOR_3, pot0.read());

			quad0.uploadSpeedCfg(speedConfig);
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
