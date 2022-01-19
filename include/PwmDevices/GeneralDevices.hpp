#ifndef C__PROJECTS_PICO_PICODRONE_INCLUDE_PWMDEVICES_HPP_
#define C__PROJECTS_PICO_PICODRONE_INCLUDE_PWMDEVICES_HPP_

#include "Types.hpp"

namespace PicoPilot::PwmDevices {

	class GeneralDevices {
	  public:
		static GeneralDevices create(const Pico::pwm_t& drivingFrequency, const Pico::gpioPin_t& setPin) noexcept;

		GeneralDevices() = default;
		GeneralDevices(const GeneralDevices&) = delete;

		GeneralDevices(GeneralDevices&&) noexcept;
		GeneralDevices& operator=(GeneralDevices&&) noexcept;

		void begin() noexcept;
		void setLevel(const uint16_t& val) noexcept;
		uint16_t getTop() const noexcept;
		void debugPrint() const noexcept;

	  protected:
		Pico::pwm_t m_frequency = 0;
		Pico::gpioPin_t m_pwmPin = NULLPIN;
		Pico::pwmWrap_t m_wrap = 0;

	  private:
		GeneralDevices(const Pico::pwm_t& drivingFrequency, const Pico::gpioPin_t& setPin) noexcept;
		Pico::pwm_t m_clockSpeed = 0;
		Pico::pwm_t m_sliceNum = 8;
		Pico::pwm_t m_channel = 2;
		Pico::pwm_t m_clockDiv = 0;
		uint16_t m_level = 0;
	};

} // namespace PicoPilot::PwmDevices

#endif // C__PROJECTS_PICO_PICODRONE_INCLUDE_PWMDEVICES_HPP_