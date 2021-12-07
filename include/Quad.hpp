#ifndef C__PROJECTS_PICO_PICODRONE_INCLUDE_QUAD_HPP_
#define C__PROJECTS_PICO_PICODRONE_INCLUDE_QUAD_HPP_

#include <array>
#include "Types.hpp"
#include "PwmDevices/MotorESC.hpp"

namespace LocalLib::Quad {
	using namespace LocalLib::PwmDevices;

	using MotorPinArray = std::array<gpioPin_t, 4>;
	using MotorLvlArray = std::array<uint16_t, 4>;
	using MotorSpeedCfg = uint64_t;

	// clang-format off
	enum Motor{
		_0 = 0, 
		_1 = 13, 
		_2 = 26, 
		_3 = 39, 
		UNASSIGNED = 52
	};
	// clang-format on

	struct MotorData {
		MotorESC controller;
		gpioPin_t pin = NULLPIN;
	};

	void
	  configureMotorSpeed(MotorSpeedCfg* config, Motor selectMotor, const uint16_t& speed) noexcept;

	class SpeedControls {
	  public:
		SpeedControls(const SpeedControls&) = delete;

		SpeedControls() noexcept {}
		SpeedControls(SpeedControls&&) noexcept;
		SpeedControls& operator=(SpeedControls&&) noexcept;

		static SpeedControls create(const MotorPinArray& controlPins) noexcept;
		void uploadSpeedCfg(MotorSpeedCfg& motorLevels) noexcept;

	  private:
		SpeedControls(const MotorPinArray& controlPins) noexcept;
		void begin();

		std::array<MotorData, 4> m_motorControls;
	};

} // namespace LocalLib::Quad

#endif // C__PROJECTS_PICO_PICODRONE_INCLUDE_QUAD_HPP_