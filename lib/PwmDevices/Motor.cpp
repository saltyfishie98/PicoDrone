#include "../Motor.hpp"

namespace LocalLib::PwmDevices {
	Motor::Motor(const GpioPin& number) {
		PwmDevices::setGpioPin(number);
	}
} // namespace LocalLib::PwmDevices