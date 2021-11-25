#include "../Helpers.hpp"

namespace LocalLib::Helpers {
	auto lastTime = Arduino::millis();

	void setInterval(const Millis& setMillis, const VoidCallback& callThis) {
		if ((Arduino::millis() - lastTime) >= setMillis) {
			callThis();
			lastTime = Arduino::millis();
		}
	}
} // namespace LocalLib::Helpers