#ifndef C__PROJECTS_PICO_PICODRONE_LIB_HELPERS_HPP_
#define C__PROJECTS_PICO_PICODRONE_LIB_HELPERS_HPP_

#include <functional>
#include "Types.hpp"

namespace LocalLib::Helpers::Misc {
	template <typename T>
	bool arrayFind(T thisElement, T inThisArray) {
		T* condition = std::find(std::begin(inThisArray), std::end(inThisArray), thisElement);
		if (condition != std::end(inThisArray))
			return true;
		return false;
	}

	void setInterval(const Millis&, const VoidCallback&);
} // namespace LocalLib::Helpers::Misc

#endif // C__PROJECTS_PICO_PICODRONE_LIB_HELPERS_HPP_
