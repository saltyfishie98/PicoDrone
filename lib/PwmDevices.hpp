#ifndef C__PROJECTS_PICO_PICODRONE_LIB_PWMDEVICES_HPP_
#define C__PROJECTS_PICO_PICODRONE_LIB_PWMDEVICES_HPP_

#include "Types.hpp"

namespace LocalLib::PwmDevices {
	class PwmDevices {
	  public:
		virtual void setGpioPin(const GpioPin& number);
		virtual void setPercent(const float& percent);
		virtual void begin();

	  private:
		float clockDiv = 64;
		float wrap = 39062;
		uint8_t servoPin = NULLPIN;
	};
} // namespace LocalLib::PwmDevices

#endif // C__PROJECTS_PICO_PICODRONE_LIB_PWMDEVICES_HPP_