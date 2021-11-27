#include "pico/stdlib.h"
#include "pico/time.h"

#include <iostream>

#include "Helpers/Pico.hpp"
#include "Pwm50Devices/Servo.hpp"
#include "Pwm50Devices/Motor.hpp"

namespace Application {

	namespace Core0 {
		void setup() {}
		void loop() {}
	} // namespace Core0

	namespace Core1 {
		using namespace LocalLib::Helpers;
		using namespace LocalLib;

		Pico::AnalogReader potentialMeter(27);
		Pwm50Devices::Motor motor(4);

		void setup() {
			potentialMeter.begin();
			motor.begin();
			motor.setLimitOffset(390.f, 160.f);
		}

		void loop() {
			float potVal = potentialMeter.read() / 4095.f;
			std::cout << "potVal%: " << potVal << "\n";

			motor.setPercent(potVal);
		}
	} // namespace Core1

} // namespace Application
