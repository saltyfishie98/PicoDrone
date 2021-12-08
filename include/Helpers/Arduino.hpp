#ifndef C__PROJECTS_PICO_PICODRONE_LIB_HELPERS_NAMESPACE_ARDUINO_HPP_
#define C__PROJECTS_PICO_PICODRONE_LIB_HELPERS_NAMESPACE_ARDUINO_HPP_

#include "pico/stdlib.h"

namespace LocalLib::Helpers::Arduino {
	template <typename T>
	T map(const T& x, const T& in_min, const T& in_max, const T& out_min, const T& out_max) {
		return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
	}

	inline uint32_t millis() {
		// TODO: refactor this to use method forced by pico sdk
#ifndef NDEBUG
		return static_cast<uint32_t>(get_absolute_time()._private_us_since_boot / 1000ull);
#else
		return static_cast<uint32_t>(get_absolute_time() / 1000ull);
#endif
	}
} // namespace LocalLib::Helpers::Arduino

#endif // C__PROJECTS_PICO_PICODRONE_LIB_HELPERS_NAMESPACE_ARDUINO_HPP_