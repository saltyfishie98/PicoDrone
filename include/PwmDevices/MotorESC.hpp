#ifndef C__PROJECTS_PICO_PICODRONE_INCLUDE_PWMDEVICES_MOTOR_HPP_
#define C__PROJECTS_PICO_PICODRONE_INCLUDE_PWMDEVICES_MOTOR_HPP_

#include "GeneralDevices.hpp"
#include "../Types.hpp"

namespace LocalLib::PwmDevices {
	class MotorESC : private GeneralDevices {
	  public:
		static MotorESC create(const gpioPin_t& setPin) noexcept;
		static uint16_t inputHalf() noexcept;

		MotorESC() = default;
		MotorESC(const MotorESC&) = delete;

		MotorESC(MotorESC&&) noexcept;
		MotorESC& operator=(MotorESC&&) noexcept;

		void setInputRange(uint16_t&& min, uint16_t&& max) noexcept;
		void setInputRange(const uint16_t& min, const uint16_t& max) noexcept;
		void setRangedLevel(const uint16_t& input) noexcept;

		using GeneralDevices::debugPrint;

	  private:
		MotorESC(const pwm_t& drivingFrequency, const gpioPin_t& setPin) noexcept;
		static uint16_t m_inputMin;
		static uint16_t m_inputMax;
		float minPercent = 0.04f;
		float maxPercent = 0.115f;
	};
} // namespace LocalLib::PwmDevices

#endif // C__PROJECTS_PICO_PICODRONE_INCLUDE_PWMDEVICES_MOTOR_HPP_