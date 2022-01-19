#ifndef C__PROJECTS_PICO_PICODRONE_INCLUDE_QUAD_HPP_
#define C__PROJECTS_PICO_PICODRONE_INCLUDE_QUAD_HPP_

#include <array>

#include "Types.hpp"
#include "PwmDevices/MotorESC.hpp"

#define Z_TRANS 0
#define XY_ROT	1
#define Z_ROT	2

namespace PicoPilot::Quad {
	class Controls {
	  public:
		Controls() = default;
		static Controls create(std::array<Pico::gpioPin_t, 4>&& pinsArray) noexcept;

		void input(int16_t&& thrust, int16_t&& yaw, int16_t&& pitch, int16_t&& roll) noexcept;
		void input(const int16_t& thrust, const int16_t& yaw, const int16_t& pitch, const int16_t& roll) noexcept;
		void debugPrint() const noexcept;
		float spdAlloc[3] = {0.7f, 0.15f, 0.15f};

	  protected:
		Controls(std::array<Pico::gpioPin_t, 4>&& pinsArray) noexcept;
		void begin() noexcept;

	  private:
		std::array<Pico::gpioPin_t, 4> m_pinsArray;
		std::array<PicoPilot::PwmDevices::MotorESC, 4> m_motors;
		int16_t m_offset = PicoPilot::PwmDevices::MotorESC::inputHalf();
	};
} // namespace PicoPilot::Quad
#endif // C__PROJECTS_PICO_PICODRONE_INCLUDE_QUAD_HPP_