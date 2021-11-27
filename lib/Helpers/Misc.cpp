#include "Helpers/Misc.hpp"

#include "Helpers/Arduino.hpp"

namespace LocalLib::Helpers::Misc {
	using namespace LocalLib::Helpers;
	auto lastTime = Arduino::millis();

	void setInterval(const Millis& setMillis, const VoidCallback& callThis) {
		if ((Arduino::millis() - lastTime) >= setMillis) {
			callThis();
			lastTime = Arduino::millis();
		}
	}
} // namespace LocalLib::Helpers::Misc