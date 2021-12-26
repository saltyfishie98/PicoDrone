#ifndef C__PROJECTS_PICO_PICODRONE_INCLUDE_QUAD_HPP_
#define C__PROJECTS_PICO_PICODRONE_INCLUDE_QUAD_HPP_

#include <array>

#include "Types.hpp"
#include "PwmDevices/MotorESC.hpp"

namespace LocalLib::Quad {
	class Controls {
	  public:
		Controls() = default;
		static Controls create(std::array<gpioPin_t, 4>&& pinsArray) noexcept;
		void input(uint16_t&& thrust, uint16_t&& yaw, uint16_t&& pitch, uint16_t&& roll) noexcept;
		void input(const uint16_t& thrust, const uint16_t& yaw, const uint16_t& pitch, const uint16_t& roll) noexcept;

	  protected:
		Controls(std::array<gpioPin_t, 4>&& pinsArray) noexcept;
		void begin() noexcept;

	  private:
		std::array<gpioPin_t, 4> m_pinsArray;
		LocalLib::PwmDevices::MotorESC m_motor0;
		LocalLib::PwmDevices::MotorESC m_motor1;
		LocalLib::PwmDevices::MotorESC m_motor2;
		LocalLib::PwmDevices::MotorESC m_motor3;
	};
} // namespace LocalLib::Quad
#endif // C__PROJECTS_PICO_PICODRONE_INCLUDE_QUAD_HPP_