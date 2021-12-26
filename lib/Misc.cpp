#include "Helpers/Misc.hpp"

#include "Helpers/Arduino.hpp"

namespace LocalLib::Helpers::Misc {
	using namespace LocalLib::Helpers;
	auto lastTime = Arduino::millis();

	bool interval(const millis_t& setMillis) {
		if ((Arduino::millis() - lastTime) >= setMillis) {
			lastTime = Arduino::millis();
			return true;
		}
		return false;
	}

	namespace Blink {
		bool toggle = 0;

		void start() {

			if (Misc::interval(250)) {
				toggle ^= 1UL << 0;
				gpio_put(PICO_DEFAULT_LED_PIN, toggle);
			}
		}

		void setup() {
			gpio_init(PICO_DEFAULT_LED_PIN);
			gpio_set_dir(PICO_DEFAULT_LED_PIN, true);
		}
	} // namespace Blink
} // namespace LocalLib::Helpers::Misc