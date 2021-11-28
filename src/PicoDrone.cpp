#include "pico/stdlib.h"

#include <iostream>
#include <stdlib.h>

#include "Helpers/Pico.hpp"
#include "Helpers/Arduino.hpp"
#include "PwmDevices.hpp"

namespace Application {
	using namespace LocalLib::Helpers::Pico;
	using namespace LocalLib::Helpers;
	using namespace LocalLib;

	AnalogReader pot0(27);
	PwmDevices servo0(50, 4);

	namespace Core0 {
		void setup() {
			pot0.begin();
			servo0.begin();
		}

		void loop() {
			uint16_t val = pot0.read();

			auto percentage = Arduino::map<uint16_t>(val, 0, 4095, 0, 12000);
			servo0.setRawLevel(percentage);
			// std::cout << "Percentage: " << val << " %\n\n";
			// sleep_ms(250);
		}
	} // namespace Core0

	namespace Core1 {
		void setup() {}
		void loop() {}
	} // namespace Core1

} // namespace Application
