#include "PwmDevices.hpp"

#include <iostream>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"

#include "ErrMacros.hpp"
#include "Helpers/Macros.hpp"

namespace LocalLib {
	PwmDevices::PwmDevices(const pwm_t& drivingFrequency, const gpioPin_t& setPin)
	  : m_frequency(drivingFrequency), m_pwmPin(setPin) {
		// ASSERT_PIN_VALID(setPin);
	}

	void PwmDevices::begin() {
		gpio_set_function(m_pwmPin, GPIO_FUNC_PWM);

		m_clockSpeed = clock_get_hz(clk_sys);
		m_sliceNum = pwm_gpio_to_slice_num(m_pwmPin);
		m_channel = pwm_gpio_to_channel(m_pwmPin);

		m_clockDiv = m_clockSpeed / m_frequency / 4096 + (m_clockSpeed % (m_frequency * 4096) != 0);

		if (m_clockDiv / 16 == 0)
			m_clockDiv = 16;

		m_wrap = m_clockSpeed * 16 / m_clockDiv / m_frequency - 1;

		pwm_set_clkdiv_int_frac(m_sliceNum, m_clockDiv / 16, m_clockDiv & 0xF);
		pwm_set_wrap(m_sliceNum, m_wrap);
		pwm_set_enabled(m_sliceNum, true);
	}

	void PwmDevices::setChannelLevel(const uint16_t& val) {
		pwm_set_chan_level(m_sliceNum, m_channel, val);
		DEBUG_RUN(std::cout << "Level: " << val << '\n';)
	}

	uint16_t PwmDevices::getTop() const {
		return m_wrap;
	}
} // namespace LocalLib