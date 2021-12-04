#include "pico/stdlib.h"

#include <iostream>
#include <stdlib.h>

#include "Helpers/Pico.hpp"
#include "Helpers/Arduino.hpp"
#include "Helpers/Misc.hpp"
#include "PwmDevices.hpp"

namespace Application {
	using namespace LocalLib::Helpers::Pico;
	using namespace LocalLib::Helpers;
	using namespace LocalLib;

	PwmDevices servo0 = PwmDevices::create(50, 4);
	uint16_t percentage = 0;

	namespace Core0 {

		void setup() {}

		void loop() {
			AnalogReader pot0 = AnalogReader::create(27);
			uint16_t val = pot0.read();

			uint low = (uint)(65465 * 0.024f);
			uint high = (uint)(65465 * 0.124f);

			percentage = Arduino::map<uint16_t>(val, 0, 4095, low, high);
		}
	} // namespace Core0

	bool toggle = 0;
	namespace Core1 {
		const uint led = PICO_DEFAULT_LED_PIN;

		void setup() {
			gpio_init(led);
			gpio_set_dir(led, true);
		}
		void loop() {
			servo0.setChannelLevel(percentage);

			if (Misc::interval(250)) {
				toggle ^= 1UL << 0;
				gpio_put(led, toggle);
			}
		}
	} // namespace Core1

} // namespace Application
