#include "pico/stdlib.h"
#include "pico/time.h"

#include <iostream>

#include "lib/Helpers.hpp"
#include "lib/Servo.hpp"

namespace Application {

	namespace Core0 {
		using namespace LocalLib::Helpers;
		using namespace LocalLib;

		Pico::AnalogReader potentialMeter(40);
		PwmDevices::Servo servo0(4);

		void setup() {}

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
		PwmDevices::Servo servo0(4);

		void setup() {}

		void loop() {
			float potVal = potentialMeter.read() / 4095.f;

			Helpers::setInterval(5000, [&potVal]() {
				std::cout << "potVal%: " << potVal << "\n";
			});

			servo0.setPercent(potVal);
		}
	} // namespace Core1
} // namespace Application
