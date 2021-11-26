#ifndef C__PROJECTS_PICO_PICODRONE_LIB_MOTOR_HPP_
#define C__PROJECTS_PICO_PICODRONE_LIB_MOTOR_HPP_

#include "PwmDevices.hpp"
#include "Types.hpp"

namespace LocalLib::PwmDevices {
	class Motor : public PwmDevices {
	  public:
		Motor();
		Motor(const GpioPin& number);

		void setLimitOffset(const float& low, const float& high = 0.f);
		void setPercent(const float& percent) override;

	  private:
		float m_lowOffset = 0;
		float m_highOffset = 0;
	};
} // namespace LocalLib::PwmDevices

#endif // C__PROJECTS_PICO_PICODRONE_LIB_MOTOR_HPP_