#include "Pwm50Devices/Servo.hpp"

namespace LocalLib::Pwm50Devices {
	Servo::Servo(const GpioPin& number) {
		Pwm50Devices::setGpioPin(number);
	}
} // namespace LocalLib::Pwm50Devices