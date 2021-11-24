#include "../Servo.hpp"

namespace LocalLib::PwmDevices {
	Servo::Servo(const GpioPin& number) {
		PwmDevices::setGpioPin(number);
	}
} // namespace LocalLib::PwmDevices