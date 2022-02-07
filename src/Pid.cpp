#include "Pid.hpp"

namespace PicoPilot {
	Pid Pid::create(const Configs& configurations) {
		Configs temp(configurations);
		return temp;
	}
} // namespace PicoPilot