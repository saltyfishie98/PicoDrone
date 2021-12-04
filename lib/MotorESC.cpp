#include "PwmDevices/MotorESC.hpp"
#include "Helpers/Arduino.hpp"

namespace LocalLib::PwmDevices {
	const pwm_t MotorESC::m_freq;

	MotorESC MotorESC::create(const gpioPin_t& setPin) {
		MotorESC temp;
		temp.m_device = GeneralDevices::create(m_freq, setPin);

		return temp;
	}

	void MotorESC::setLevelScale(uint16_t&& inputMin, uint16_t&& inputMax) {
		m_inputMin = inputMin;
		m_inputMax = inputMax;
	}

	void MotorESC::setLevel(const uint16_t& input) {
		using namespace Helpers;
		auto level =
		  Arduino::map(input, m_inputMin, m_inputMax, (uint16_t)(m_device.getTop() * minPercent),
					   (uint16_t)(m_device.getTop() * maxPercent));

		m_device.setChannelLevel(level);
	}
} // namespace LocalLib::PwmDevices