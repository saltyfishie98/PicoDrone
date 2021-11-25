#ifndef C__PROJECTS_PICO_PICODRONE_LIB_SERVO_HPP_
#define C__PROJECTS_PICO_PICODRONE_LIB_SERVO_HPP_

#include "PwmDevices.hpp"
#include "Types.hpp"

namespace LocalLib::PwmDevices {
	class Motor : public PwmDevices {
	  public:
		Motor();
		Motor(const GpioPin& number);
	};
} // namespace LocalLib::PwmDevices

#endif // C__PROJECTS_PICO_PICODRONE_LIB_SERVO_HPP_