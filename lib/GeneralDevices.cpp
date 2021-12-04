#include "PwmDevices/GeneralDevices.hpp"

#include <iostream>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"

#include "ErrMacros.hpp"
#include "Helpers/Macros.hpp"

namespace LocalLib::PwmDevices {
	GeneralDevices::GeneralDevices(const pwm_t& drivingFrequency, const gpioPin_t& setPin)
	  : m_frequency(drivingFrequency), m_pwmPin(setPin) {
		// ASSERT_PIN_VALID(setPin);
	}

	GeneralDevices::GeneralDevices(GeneralDevices&& other) noexcept {
		m_pwmPin = other.m_pwmPin;
		m_frequency = other.m_frequency;
		m_clockSpeed = other.m_clockSpeed;
		m_sliceNum = other.m_sliceNum;
		m_channel = other.m_channel;
		m_clockDiv = other.m_clockDiv;
		m_wrap = other.m_wrap;
	}

	GeneralDevices& GeneralDevices::operator=(GeneralDevices&& other) {
		if (this != &other) {
			m_pwmPin = other.m_pwmPin;
			m_frequency = other.m_frequency;
			m_clockSpeed = other.m_clockSpeed;
			m_sliceNum = other.m_sliceNum;
			m_channel = other.m_channel;
			m_clockDiv = other.m_clockDiv;
			m_wrap = other.m_wrap;
		}

		return *this;
	}

	GeneralDevices GeneralDevices::create(const pwm_t& drivingFrequency, const gpioPin_t& setPin) {
		GeneralDevices temp(drivingFrequency, setPin);
		temp.begin();
		return temp;
	}

	void GeneralDevices::begin() {
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

	void GeneralDevices::setChannelLevel(const uint16_t& val) {
		pwm_set_chan_level(m_sliceNum, m_channel, val);
		DEBUG_RUN(std::cout << "Level: " << val << '\n';)
	}

	uint16_t GeneralDevices::getTop() const {
		return m_wrap;
	}
} // namespace LocalLib::PwmDevices