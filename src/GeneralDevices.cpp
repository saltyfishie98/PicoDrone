#include "PwmDevices/GeneralDevices.hpp"

#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"

#include "ErrMacros.hpp"
#include "Helpers/Macros.hpp"

namespace PicoPilot::PwmDevices {
	GeneralDevices::GeneralDevices(const Pico::pwm_t& drivingFrequency, const Pico::gpioPin_t& setPin)
	  : m_frequency(drivingFrequency), m_pwmPin(setPin) {}

	GeneralDevices::GeneralDevices(GeneralDevices&& other) {
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

	/**
	 * @brief Factory method to create an instance of PwmDevices::GeneralDevices
	 *
	 * @param drivingFrequency The frequency of the pwm signal
	 * @param setPin The gpio pin number
	 * @return GeneralDevices
	 */
	GeneralDevices GeneralDevices::create(const Pico::pwm_t& drivingFrequency, const Pico::gpioPin_t& setPin) {
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

	/**
	 * @brief Set the level of the pwm signal
	 *
	 * @param val literal value that is smaller than the wrap value
	 */
	void GeneralDevices::setLevel(const uint16_t& val) {
		DEBUG_RUN(m_level = val;)
		pwm_set_chan_level(m_sliceNum, m_channel, val);
	}

	/**
	 * @brief Returns the wrap value
	 *
	 * @return uint16_t
	 */
	uint16_t GeneralDevices::getTop() const {
		return m_wrap;
	}

	void GeneralDevices::debugPrint() const {
		DEBUG_RUN(printf("GeneralDevices.cpp: INFO: duty percent: %f\n", (float)m_level / (float)m_wrap);)
	}
} // namespace PicoPilot::PwmDevices