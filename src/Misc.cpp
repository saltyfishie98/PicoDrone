#include "Helpers/Misc.hpp"

#include "hardware/timer.h"

namespace PicoPilot::Misc {
	using namespace PicoPilot;

	namespace {
		bool toggle = 0;
		auto last = get_absolute_time();
	} // namespace

	namespace Blink {

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
		void run(uint interval) {
			static auto now = get_absolute_time();
			if (absolute_time_diff_us(last, now) / 1000 > interval) {
				toggle ^= 1UL << 0;
				gpio_put(PICO_DEFAULT_LED_PIN, toggle);
				last = now;
			}
		}

	} // namespace Blink
} // namespace PicoPilot::Misc