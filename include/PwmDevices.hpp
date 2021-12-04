#ifndef C__PROJECTS_PICO_PICODRONE_INCLUDE_PWMDEVICES_HPP_
#define C__PROJECTS_PICO_PICODRONE_INCLUDE_PWMDEVICES_HPP_

#include "Types.hpp"

namespace LocalLib {

	class PwmDevices {
	  public:
		static PwmDevices create(const pwm_t& drivingFrequency, const gpioPin_t& setPin) noexcept;
		void setChannelLevel(const uint16_t& percent) noexcept;
		uint16_t getTop() const;

	  private:
		PwmDevices() noexcept {};
		PwmDevices(const PwmDevices&) noexcept {}
		PwmDevices(PwmDevices&&) noexcept {}
		PwmDevices(const pwm_t& drivingFrequency, const gpioPin_t& setPin) noexcept;
		void begin() noexcept;

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