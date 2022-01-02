#ifndef C__PROJECTS_PICO_PICODRONE_INCLUDE_PWMDEVICES_HPP_
#define C__PROJECTS_PICO_PICODRONE_INCLUDE_PWMDEVICES_HPP_

#include "Types.hpp"

namespace LocalLib::PwmDevices {

	class GeneralDevices {
	  public:
		static GeneralDevices create(const pwm_t& drivingFrequency, const gpioPin_t& setPin) noexcept;

		GeneralDevices() = default;
		GeneralDevices(const GeneralDevices&) = delete;

		GeneralDevices(GeneralDevices&&) noexcept;
		GeneralDevices& operator=(GeneralDevices&&) noexcept;

		void begin() noexcept;
		void setLevel(const uint16_t& val) noexcept;
		uint16_t getTop() const noexcept;
		void debugPrint() const noexcept;

	  protected:
		pwm_t m_frequency = 0;
		gpioPin_t m_pwmPin = NULLPIN;
		pwmWrap_t m_wrap = 0;

	  private:
		GeneralDevices(const pwm_t& drivingFrequency, const gpioPin_t& setPin) noexcept;
		pwm_t m_clockSpeed = 0;
		pwm_t m_sliceNum = 8;
		pwm_t m_channel = 2;
		pwm_t m_clockDiv = 0;
		uint16_t m_level = 0;
	};

} // namespace LocalLib::PwmDevices

#endif // C__PROJECTS_PICO_PICODRONE_INCLUDE_PWMDEVICES_HPP_