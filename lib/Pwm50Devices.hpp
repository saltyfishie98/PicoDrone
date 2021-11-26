#ifndef C__PROJECTS_PICO_PICODRONE_LIB_PWMDEVICES_HPP_
#define C__PROJECTS_PICO_PICODRONE_LIB_PWMDEVICES_HPP_

#include "Types.hpp"

namespace LocalLib::Pwm50Devices {
	/**
	 * @brief Base class for class made for controlling devices that uses a 5ohz pwm signal
	 *
	 */
	class Pwm50Devices {
	  public:
		/**
		 * @brief Set the GPIO pin where the pwm device is connected to
		 *
		 * @param number GPIO pin number
		 */
		virtual void setGpioPin(const GpioPin& number);

		/**
		 * @brief Set the duty cycle percentage (0 to 1)
		 *
		 * @param percent
		 */
		virtual void setPercent(const float& percent);
		virtual void begin();

	  protected:
		float clockDiv = 64;
		float wrap = 39062;
		uint8_t servoPin = NULLPIN;
	};
} // namespace LocalLib::Pwm50Devices

#endif // C__PROJECTS_PICO_PICODRONE_LIB_PWMDEVICES_HPP_