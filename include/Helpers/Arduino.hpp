#ifndef C__PROJECTS_PICO_PICODRONE_LIB_HELPERS_NAMESPACE_ARDUINO_HPP_
#define C__PROJECTS_PICO_PICODRONE_LIB_HELPERS_NAMESPACE_ARDUINO_HPP_

#include "pico/stdlib.h"

namespace PicoPilot::Arduino {
	template <typename T>
	constexpr T map(const T& x, const T& in_min, const T& in_max, const T& out_min, const T& out_max) {
		return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
	}

	template <typename T>
	constexpr T constrain(T value, T low, T high) {
		return (value) < (low) ? (low) : ((value) > (high) ? (high) : (value));
	}
} // namespace PicoPilot::Arduino

#endif // C__PROJECTS_PICO_PICODRONE_LIB_HELPERS_NAMESPACE_ARDUINO_HPP_