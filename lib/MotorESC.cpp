#include "PwmDevices/MotorESC.hpp"
#include "Helpers/Arduino.hpp"

namespace LocalLib::PwmDevices {
	const pwm_t MotorESC::m_freq;

	MotorESC::MotorESC(MotorESC&& other) {
		m_device = std::move(other.m_device);
		m_inputMin = other.m_inputMin;
		m_inputMax = other.m_inputMax;
		minPercent = other.minPercent;
		maxPercent = other.maxPercent;
	}

	MotorESC& MotorESC::operator=(MotorESC&& other) {
		if (this != &other) {
			m_device = std::move(other.m_device);
			m_inputMin = other.m_inputMin;
			m_inputMax = other.m_inputMax;
			minPercent = other.minPercent;
			maxPercent = other.maxPercent;
		}

		return *this;
	}

	MotorESC MotorESC::create(const gpioPin_t& setPin) {
		MotorESC temp;
		temp.m_device = GeneralDevices::create(m_freq, setPin);

		return temp;
	}

	void MotorESC::setInputRange(uint16_t&& min, uint16_t&& max) {
		m_inputMin = min;
		m_inputMax = max;
	}

	void MotorESC::setInputRange(const uint16_t& min, const uint16_t& max) {
		m_inputMin = min;
		m_inputMax = max;
	}

	/**
	 * @brief Set the pwm level that controls the motor esc
	 *
	 * @param input literal input
	 */
	void MotorESC::setLevel(const uint16_t& input) {
		using namespace Helpers;
		auto level = Arduino::map(input, m_inputMin, m_inputMax, (uint16_t)(m_device.getTop() * minPercent),
								  (uint16_t)(m_device.getTop() * maxPercent));

		m_device.setChannelLevel(level);
	}
} // namespace LocalLib::PwmDevices