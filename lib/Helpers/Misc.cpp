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
} // namespace LocalLib::Helpers::Misc