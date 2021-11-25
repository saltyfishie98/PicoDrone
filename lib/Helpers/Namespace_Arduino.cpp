#include "Namespace_Arduino.hpp"

#include "pico/time.h"

namespace LocalLib::Helpers::Arduino {
	uint32_t millis() {
		return static_cast<uint32_t>(get_absolute_time()._private_us_since_boot / 1000ull);
	}
} // namespace LocalLib::Helpers::Arduino