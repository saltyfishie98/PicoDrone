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
		void debugPrint() const noexcept;

	  protected:
		Controls(std::array<gpioPin_t, 4>&& pinsArray) noexcept;
		void begin() noexcept;

	  private:
		std::array<gpioPin_t, 4> m_pinsArray;
		std::array<LocalLib::PwmDevices::MotorESC, 4> m_motors;
	};
} // namespace LocalLib::Quad
#endif // C__PROJECTS_PICO_PICODRONE_INCLUDE_QUAD_HPP_