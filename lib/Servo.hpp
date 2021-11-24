#ifndef C__PROJECTS_PICO_PICODRONE_LIB_SERVO_HPP_
#define C__PROJECTS_PICO_PICODRONE_LIB_SERVO_HPP_

#include "PwmDevices.hpp"
#include "Types.hpp"

namespace LocalLib {
	class Servo : public PwmDevices {
	  public:
		Servo();
		Servo(const GpioPin& number);
	};
} // namespace LocalLib

#endif // C__PROJECTS_PICO_PICODRONE_LIB_SERVO_HPP_