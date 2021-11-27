#ifndef C__PROJECTS_PICO_PICODRONE_LIB_SERVO_HPP_
#define C__PROJECTS_PICO_PICODRONE_LIB_SERVO_HPP_

#include "Bases/Pwm50Devices.hpp"
#include "Types.hpp"

namespace LocalLib::Pwm50Devices {
	class Servo : public Pwm50Devices {
	  public:
		Servo();
		Servo(const GpioPin& number);
	};
} // namespace LocalLib::Pwm50Devices

#endif // C__PROJECTS_PICO_PICODRONE_LIB_SERVO_HPP_