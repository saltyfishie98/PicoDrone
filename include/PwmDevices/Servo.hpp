#ifndef C__PROJECTS_PICO_PICODRONE_INCLUDE_PWMDEVICES_SERVO_HPP_
#define C__PROJECTS_PICO_PICODRONE_INCLUDE_PWMDEVICES_SERVO_HPP_

#include "GeneralDevices.hpp"
#include "../Types.hpp"

namespace LocalLib::PwmDevices {
	class Servo : private GeneralDevices {
	  public:
		static Servo create(const gpioPin_t& setPin) noexcept;

		Servo() = default;
		Servo(const Servo&) = delete;

		Servo(Servo&&) noexcept;
		Servo& operator=(Servo&&) noexcept;

		void setInputRange(uint16_t&& max, uint16_t&& min) noexcept;
		void setInputRange(const uint16_t& max, const uint16_t& min) noexcept;
		void setRangedLevel(const uint16_t& input) noexcept;
		using GeneralDevices::debugPrint;

	  private:
		Servo(const pwm_t& drivingFrequency, const gpioPin_t& setPin) noexcept;
		uint16_t m_inputMin = 0;
		uint16_t m_inputMax = 4095;
		float minPercent = 0.024f;
		float maxPercent = 0.124f;
	};
} // namespace LocalLib::PwmDevices

#endif // C__PROJECTS_PICO_PICODRONE_INCLUDE_PWMDEVICES_SERVO_HPP_