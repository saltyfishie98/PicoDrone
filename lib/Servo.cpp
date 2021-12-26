#include "PwmDevices/Servo.hpp"
#include "Helpers/Arduino.hpp"
#include "Helpers/Macros.hpp"

namespace LocalLib::PwmDevices {
	const pwm_t Servo::m_freq;

	Servo Servo::create(const gpioPin_t& setPin) {
		Servo temp;
		temp.m_device = GeneralDevices::create(Servo::m_freq, setPin);

		return temp;
	}

	void Servo::setInputRange(uint16_t&& min, uint16_t&& max) {
		DEBUG_RUN(std::cout << "Server.cpp: setInputRange(): INFO: data moved\n";)
		m_inputMin = min;
		m_inputMax = max;
	}

	void Servo::setInputRange(const uint16_t& min, const uint16_t& max) {
		DEBUG_RUN(std::cout << "Server.cpp: setInputRange(): INFO: const ref data\n";)
		m_inputMin = min;
		m_inputMax = max;
	}

	void Servo::setLevel(uint16_t&& input) {
		DEBUG_RUN(std::cout << "Server.cpp: setLevel(): INFO: data moved\n";)
		using namespace Helpers;
		auto level = Arduino::map(input, m_inputMin, m_inputMax, (uint16_t)(m_device.getTop() * minPercent),
								  (uint16_t)(m_device.getTop() * maxPercent));

		m_device.setChannelLevel(level);
	}

	void Servo::setLevel(const uint16_t& input) {
		DEBUG_RUN(std::cout << "Server.cpp: setLevel(): INFO: const ref data\n";)
		using namespace Helpers;
		auto level = Arduino::map(input, m_inputMin, m_inputMax, (uint16_t)(m_device.getTop() * minPercent),
								  (uint16_t)(m_device.getTop() * maxPercent));

		m_device.setChannelLevel(level);
	}
} // namespace LocalLib::PwmDevices