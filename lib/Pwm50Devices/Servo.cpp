#include "Pwm50Devices/Servo.hpp"

namespace LocalLib::Pwm50Devices {
	Servo::Servo(const GpioPin_t& number) {
		Pwm50Devices::setGpioPin(number);
	}
} // namespace LocalLib::Pwm50Devices