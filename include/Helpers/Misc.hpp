#ifndef C__PROJECTS_PICO_PICODRONE_LIB_HELPERS_HPP_
#define C__PROJECTS_PICO_PICODRONE_LIB_HELPERS_HPP_

#include "Types.hpp"
#include "pico/stdlib.h"
#include "stdio.h"
#include "Helpers/Macros.hpp"

namespace PicoPilot::Misc {

	namespace Blink {
		void start(uint interval) noexcept;
		void setup() noexcept;
	} // namespace Blink

	template <typename T>
	bool arrayFind(T thisElement, T inThisArray) noexcept {
		T* condition = std::find(std::begin(inThisArray), std::end(inThisArray), thisElement);
		if (condition != std::end(inThisArray))
			return true;
		return false;
	}

	template <typename T>
	inline T milli(const T& value) noexcept {
		T out = (float)value * 1000.f;
		return out;
	}

	inline void clearConsole() {
		DEBUG_RUN(printf("\033[2J");)
	}

	bool interval(const Pico::millis_t& setMillis) noexcept;
} // namespace PicoPilot::Misc

#endif // C__PROJECTS_PICO_PICODRONE_LIB_HELPERS_HPP_
