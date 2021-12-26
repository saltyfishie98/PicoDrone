#ifndef C__PROJECTS_PICO_PICODRONE_INCLUDE_PWMDEVICES_HPP_
#define C__PROJECTS_PICO_PICODRONE_INCLUDE_PWMDEVICES_HPP_

#include "Types.hpp"

namespace LocalLib::PwmDevices {

	class GeneralDevices {
	  public:
		GeneralDevices(const GeneralDevices&) = delete;

		GeneralDevices() noexcept {}
		GeneralDevices(GeneralDevices&&) noexcept;
		GeneralDevices& operator=(GeneralDevices&&) noexcept;

		static GeneralDevices create(const pwm_t& drivingFrequency, const gpioPin_t& setPin) noexcept;
		void setLevel(const uint16_t& val) noexcept;
		uint16_t getTop() const;

	  protected:
		GeneralDevices(const pwm_t& drivingFrequency, const gpioPin_t& setPin) noexcept;
		void begin() noexcept;

	  private:
		gpioPin_t m_pwmPin = NULLPIN;
		pwm_t m_frequency = 0;
		pwm_t m_clockSpeed = 0;
		pwm_t m_sliceNum = 8;
		pwm_t m_channel = 2;
		pwm_t m_clockDiv = 0;
		pwmWrap_t m_wrap = 0;
	};

} // namespace LocalLib::PwmDevices

#endif // C__PROJECTS_PICO_PICODRONE_INCLUDE_PWMDEVICES_HPP_