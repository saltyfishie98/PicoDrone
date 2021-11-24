#include "../Servo.hpp"

namespace LocalLib {
	Servo::Servo(const GpioPin& number) {
		PwmDevices::setGpioPin(number);
	}
} // namespace LocalLib