#include "PwmDevices/Servo.hpp"
#include "Helpers/Arduino.hpp"
#include "Helpers/Macros.hpp"

namespace LocalLib::PwmDevices {
	Servo::Servo(Servo&& other) {
		m_inputMin = other.m_inputMin;
		m_inputMax = other.m_inputMax;
		minPercent = other.minPercent;
		maxPercent = other.maxPercent;
		GeneralDevices::m_frequency = other.m_frequency;
		GeneralDevices::m_pwmPin = other.m_pwmPin;

		GeneralDevices::begin();
	}

	Servo& Servo::operator=(Servo&& other) {
		if (this != &other) {
			m_inputMin = other.m_inputMin;
			m_inputMax = other.m_inputMax;
			minPercent = other.minPercent;
			maxPercent = other.maxPercent;
			GeneralDevices::m_frequency = other.m_frequency;
			GeneralDevices::m_pwmPin = other.m_pwmPin;

			GeneralDevices::begin();
		}

		return *this;
	}

	Servo Servo::create(const gpioPin_t& setPin) {
		Servo temp;
		temp.m_frequency = 50;
		temp.m_pwmPin = setPin;
		temp.begin();

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
	void Servo::setRangedLevel(const uint16_t& input) {
		DEBUG_RUN(std::cout << "Server.cpp: setRangedLevel(): INFO: const ref data\n";)
		using namespace LocalLib;
		auto level = Arduino::map(input, m_inputMin, m_inputMax, (uint16_t)(GeneralDevices::getTop() * minPercent),
								  (uint16_t)(GeneralDevices::getTop() * maxPercent));

		GeneralDevices::setLevel(level);
	}
} // namespace LocalLib::PwmDevices