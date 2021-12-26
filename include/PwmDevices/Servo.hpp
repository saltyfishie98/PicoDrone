#ifndef C__PROJECTS_PICO_PICODRONE_INCLUDE_PWMDEVICES_SERVO_HPP_
#define C__PROJECTS_PICO_PICODRONE_INCLUDE_PWMDEVICES_SERVO_HPP_

#include "GeneralDevices.hpp"
#include "../Types.hpp"

namespace LocalLib::PwmDevices {
	class Servo {
	  public:
		Servo(const Servo&) = delete;
		static Servo create(const gpioPin_t& setPin) noexcept;
		void setInputRange(uint16_t&& max, uint16_t&& min) noexcept;
		void setInputRange(const uint16_t& max, const uint16_t& min) noexcept;
		void setLevel(uint16_t&& input) noexcept;
		void setLevel(const uint16_t& input) noexcept;

	  protected:
		Servo() noexcept {}
		Servo(Servo&&) noexcept;
		Servo(const pwm_t& drivingFrequency, const gpioPin_t& setPin) noexcept;

	  private:
		GeneralDevices m_device;
		const static pwm_t m_freq = 50;
		uint16_t m_inputMin = 0;
		uint16_t m_inputMax = 4065;
		float minPercent = 0.024f;
		float maxPercent = 0.124f;
	};
} // namespace LocalLib::PwmDevices

#endif // C__PROJECTS_PICO_PICODRONE_INCLUDE_PWMDEVICES_SERVO_HPP_