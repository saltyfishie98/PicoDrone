#ifndef C__PROJECTS_PICO_PICODRONE_LIB_HELPERS_HPP_
#define C__PROJECTS_PICO_PICODRONE_LIB_HELPERS_HPP_

#include "Types.hpp"
#include "pico/stdlib.h"

namespace PicoPilot::Misc {

	template <typename T>
	bool arrayFind(T thisElement, T inThisArray) noexcept {
		T* condition = std::find(std::begin(inThisArray), std::end(inThisArray), thisElement);
		if (condition != std::end(inThisArray))
			return true;
		return false;
	}

	bool interval(const Pico::millis_t& setMillis) noexcept;

	namespace Blink {
		void start() noexcept;
		void setup() noexcept;
	} // namespace Blink
} // namespace PicoPilot::Misc

#endif // C__PROJECTS_PICO_PICODRONE_LIB_HELPERS_HPP_
