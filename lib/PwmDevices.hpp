#ifndef C__PROJECTS_PICO_PICODRONE_LIB_PWMDEVICES_HPP_
#define C__PROJECTS_PICO_PICODRONE_LIB_PWMDEVICES_HPP_

#include <stdint.h>

namespace LocalLib {
	using GpioPin = uint8_t;

	class PwmDevices {
	  public:
		virtual void setGpioPin(const GpioPin& number);
		virtual void setPercent(const float& percent);

	  private:
		float clockDiv = 64;
		float wrap = 39062;
		uint8_t servoPin = 29;
	};
} // namespace LocalLib

#endif // C__PROJECTS_PICO_PICODRONE_LIB_PWMDEVICES_HPP_