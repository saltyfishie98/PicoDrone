#ifndef C__PROJECTS_PICO_PICODRONE_LIB_MOTOR_HPP_
#define C__PROJECTS_PICO_PICODRONE_LIB_MOTOR_HPP_

#include "Bases/Pwm50Devices.hpp"
#include "Types.hpp"

namespace LocalLib::Pwm50Devices {
	class Motor : public Pwm50Devices {
	  public:
		Motor();
		Motor(const GpioPin& number);

		void setLimitOffset(const float& low, const float& high = 0.f);
		void setPercent(const float& percent) override;

	  private:
		float m_lowOffset = 0;
		float m_highOffset = 0;
	};
} // namespace LocalLib::Pwm50Devices

#endif // C__PROJECTS_PICO_PICODRONE_LIB_MOTOR_HPP_