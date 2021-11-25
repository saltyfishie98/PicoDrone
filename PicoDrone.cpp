#include "pico/stdlib.h"

#include <iostream>

#include "lib/Helpers.hpp"
#include "lib/Servo.hpp"

namespace Application {
	using namespace LocalLib::Helpers;
	using namespace LocalLib;

	Pico::AnalogReader potentialMeter(27);
	PwmDevices::Servo servo0(4);

	void setup() {}

	void loop() {
		float potVal = potentialMeter.read() / 4095.f;
		std::cout << "potVal%: " << potVal << "\n";

		servo0.setPercent(potVal);
	}
} // namespace Application
