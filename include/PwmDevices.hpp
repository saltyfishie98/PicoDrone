#ifndef C__PROJECTS_PICO_PICODRONE_INCLUDE_PWMDEVICES_HPP_
#define C__PROJECTS_PICO_PICODRONE_INCLUDE_PWMDEVICES_HPP_

#include "Types.hpp"
#include "Interfaces.hpp"

namespace LocalLib {

	class PwmDevices : public IClass {
	  public:
		PwmDevices(const pwm_t& drivingFrequency, const gpioPin_t& setPin);

		void begin() override;
		void setChannelLevel(const uint16_t& percent);
		uint16_t getTop() const;

	  private:
		gpioPin_t m_pwmPin = NULLPIN;
		pwm_t m_frequency = 0;
		pwm_t m_clockSpeed = 0;
		pwm_t m_sliceNum = 8;
		pwm_t m_channel = 2;
		pwm_t m_clockDiv = 0;
		pwmWrap_t m_wrap = 0;
	};

} // namespace LocalLib

#endif // C__PROJECTS_PICO_PICODRONE_INCLUDE_PWMDEVICES_HPP_