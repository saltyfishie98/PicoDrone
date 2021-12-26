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

	/**
	 * @brief Configure the range of the input for use in the Arduino's map function
	 *
	 * @param min The minimum value of the input
	 * @param max The maximum value of the input
	 */
	void Servo::setInputRange(uint16_t&& min, uint16_t&& max) {
		DEBUG_RUN(std::cout << "Server.cpp: setInputRange(): INFO: data moved\n";)
		m_inputMin = min;
		m_inputMax = max;
	}

	/**
	 * @brief Configure the range of the input for use in the Arduino's map function
	 *
	 * @param min The minimum value of the input
	 * @param max The maximum value of the input
	 */
	void Servo::setInputRange(const uint16_t& min, const uint16_t& max) {
		DEBUG_RUN(std::cout << "Server.cpp: setInputRange(): INFO: const ref data\n";)
		m_inputMin = min;
		m_inputMax = max;
	}

	/**
	 * @brief Set the pwm level that controls the motor esc
	 *
	 * @param input literal input
	 */
	void Servo::setLevel(const uint16_t& input) {
		DEBUG_RUN(std::cout << "Server.cpp: setLevel(): INFO: const ref data\n";)
		using namespace Helpers;
		auto level = Arduino::map(input, m_inputMin, m_inputMax, (uint16_t)(m_device.getTop() * minPercent),
								  (uint16_t)(m_device.getTop() * maxPercent));

		m_device.setLevel(level);
	}
} // namespace LocalLib::PwmDevices