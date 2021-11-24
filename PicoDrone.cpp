#include "pico/stdlib.h"

#include <iostream>

#include "lib/Helpers.hpp"
#include "lib/Servo.hpp"

int Application() {
	using namespace LocalLib::Helpers;

	Pico::AnalogReader potentialMeter(27);
	LocalLib::Servo servo0(4);

	while (true) {
		float potVal = potentialMeter.read() / 4095.f;
		std::cout << "potVal%: " << potVal << "\n";

		servo0.setPercent(potVal);
	}
}
