#ifndef C__PROJECTS_PICO_PICODRONE_INCLUDE_PWMDEVICES_MOTOR_HPP_
#define C__PROJECTS_PICO_PICODRONE_INCLUDE_PWMDEVICES_MOTOR_HPP_

#include "GeneralDevices.hpp"
#include "../Types.hpp"

namespace LocalLib::PwmDevices {
	class MotorESC {
	  public:
		MotorESC(const MotorESC&) = delete;
		static MotorESC create(const gpioPin_t& setPin) noexcept;
		void setLevelScale(uint16_t&& inputMin, uint16_t&& inputMax) noexcept;
		void setLevel(const uint16_t& input) noexcept;

	  protected:
		MotorESC() noexcept {}
		MotorESC(MotorESC&&) noexcept;
		MotorESC(const pwm_t& drivingFrequency, const gpioPin_t& setPin) noexcept;

	  private:
		GeneralDevices m_device;
		const static pwm_t m_freq = 50;
		uint16_t m_inputMin = 0;
		uint16_t m_inputMax = 4065;
		float minPercent = 0.035f;
		float maxPercent = 0.115f;
	};
} // namespace LocalLib::PwmDevices

#endif // C__PROJECTS_PICO_PICODRONE_INCLUDE_PWMDEVICES_MOTOR_HPP_