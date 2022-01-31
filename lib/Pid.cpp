#include "Pid.hpp"

namespace PicoPilot {
	Pid Pid::create(Configs&& configurations) {
		Configs temp(configurations);
		return temp;
	}
} // namespace PicoPilot