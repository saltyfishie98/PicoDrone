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

	namespace Core0 {
		AnalogReader pot0 = AnalogReader::create(27);
		PwmDevices servo0 = PwmDevices::create(50, 4);

		void setup() {}

		void loop() {
			uint16_t val = pot0.read();

			uint low = (uint)(65465 * 0.024f);
			uint high = (uint)(65465 * 0.124f);

			auto percentage = Arduino::map<uint16_t>(val, 0, 4095, low, high);
			servo0.setChannelLevel(percentage);
		}
	} // namespace Core0

	namespace Core1 {
		void setup() {}
		void loop() {}
	} // namespace Core1

} // namespace Application
