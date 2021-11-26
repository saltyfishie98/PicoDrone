#include "../Motor.hpp"

#include "hardware/pwm.h"
#include <iostream>

#include "../Helpers.hpp"

namespace LocalLib::PwmDevices {
	Motor::Motor(const GpioPin& number) {
		PwmDevices::setGpioPin(number);
	}

	void Motor::setLimitOffset(const float& low, const float& high) {
		m_lowOffset = low;

		if (!high == 0.f)
			m_highOffset = high;
		else
			m_highOffset = low;
	}

	void Motor::setPercent(const float& percent) {
		using namespace Helpers;
		float millis = Arduino::map(percent, 0.f, 1.f, 400.f + m_lowOffset, 2400.f - m_highOffset);
		DEBUG_RUN(std::cout << "millis: " << millis << "\n\n";)
		pwm_set_gpio_level(PwmDevices::servoPin, (millis / 20000.f) * wrap);
	}
} // namespace LocalLib::PwmDevices