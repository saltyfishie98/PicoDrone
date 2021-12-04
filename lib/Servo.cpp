#include "PwmDevices/Servo.hpp"
#include "Helpers/Arduino.hpp"

namespace LocalLib::PwmDevices {
	const pwm_t Servo::m_freq;

	Servo Servo::create(const gpioPin_t& setPin) {
		Servo temp;
		temp.m_device = GeneralDevices::create(Servo::m_freq, setPin);

		return temp;
	}

	void Servo::setLevelScale(uint16_t&& inputMin, uint16_t&& inputMax) {
		m_inputMin = inputMin;
		m_inputMax = inputMax;
	}

	void Servo::setLevel(const uint16_t& input) {
		using namespace Helpers;
		auto level =
		  Arduino::map(input, m_inputMin, m_inputMax, (uint16_t)(m_device.getTop() * minPercent),
					   (uint16_t)(m_device.getTop() * maxPercent));

		m_device.setChannelLevel(level);
	}
} // namespace LocalLib::PwmDevices