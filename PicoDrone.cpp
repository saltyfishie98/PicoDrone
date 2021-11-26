#include "pico/stdlib.h"
#include "pico/time.h"

#include <iostream>

#include "lib/Helpers.hpp"
#include "lib/Servo.hpp"
#include "lib/Motor.hpp"

namespace Application {

	namespace Core0 {
		using namespace LocalLib::Helpers;
		using namespace LocalLib;

		PwmDevices::Servo servo0(77);
		Pico::AnalogReader potentialMeter(40);

		void setup() {
			servo0.begin();
			potentialMeter.begin();
		}

		void loop() {
			float potVal = potentialMeter.read() / 4095.f;

			Helpers::setInterval(5000, [&potVal]() {
				std::cout << "potVal%: " << potVal << "\n";
			});

			servo0.setPercent(potVal);
		}
	} // namespace Core0

	namespace Core1 {
		using namespace LocalLib::Helpers;
		using namespace LocalLib;

		Pico::AnalogReader potentialMeter(27);
		PwmDevices::Motor motor(4);

		void setup() {
			potentialMeter.begin();
			motor.begin();
			motor.setLimitOffset(390.f, 160.f);
		}

		void loop() {
			float potVal = potentialMeter.read() / 4095.f;

			Helpers::setInterval(5000, [&potVal]() {
				std::cout << "potVal%: " << potVal << "\n";
			});

			motor.setPercent(potVal);
		}
	} // namespace Core1
} // namespace Application
