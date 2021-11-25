#ifndef C__PROJECTS_PICO_PICODRONE_LIB_HELPERS_NAMESPACE_ARDUINO_HPP_
#define C__PROJECTS_PICO_PICODRONE_LIB_HELPERS_NAMESPACE_ARDUINO_HPP_

#include "pico/stdlib.h"

namespace LocalLib::Helpers::Arduino {
	template <typename T>
	T map(T x, T in_min, T in_max, T out_min, T out_max) {
		return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
	}

	uint32_t millis();
} // namespace LocalLib::Helpers::Arduino

#endif // C__PROJECTS_PICO_PICODRONE_LIB_HELPERS_NAMESPACE_ARDUINO_HPP_