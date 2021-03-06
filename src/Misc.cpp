#include "Helpers/Misc.hpp"

#include "Helpers/Arduino.hpp"

namespace PicoPilot::Misc {
	using namespace PicoPilot;

	namespace {
		auto lastTime = Arduino::millis();
	}

	bool interval(const Pico::millis_t& setMillis) {
		if ((Arduino::millis() - lastTime) >= setMillis) {
			lastTime = Arduino::millis();
			return true;
		}
		return false;
	}

	namespace Blink {
		namespace {
			bool toggle = 0;
		}

		/**
		 * @brief Setup blink using the built-in LED(just place in setup)
		 *
		 */
		void setup() {
			gpio_init(PICO_DEFAULT_LED_PIN);
			gpio_set_dir(PICO_DEFAULT_LED_PIN, true);
		}

		/**
		 * @brief start the blinking of the built-in LED
		 *
		 */
		void start(uint interval) {
			if (Misc::interval(interval)) {
				toggle ^= 1UL << 0;
				gpio_put(PICO_DEFAULT_LED_PIN, toggle);
			}
		}

	} // namespace Blink
} // namespace PicoPilot::Misc