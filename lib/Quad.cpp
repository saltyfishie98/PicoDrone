#include "Quad.hpp"
#include "Helpers/Macros.hpp"

#include <iostream>

namespace LocalLib::Quad {
	SpeedControls::SpeedControls(const MotorPinArray& controlPins) {
		uint8_t i = 0;
		for (auto controlPin : controlPins) {
			m_motorControls[i].pin = controlPin;
			++i;
		}
	}

	SpeedControls::SpeedControls(SpeedControls&& other) {
		m_motorControls = std::move(other.m_motorControls);
	}

	SpeedControls& SpeedControls::operator=(SpeedControls&& other) {
		if (this != &other) {
			m_motorControls = std::move(other.m_motorControls);
		}

		return *this;
	}

	SpeedControls SpeedControls::create(const MotorPinArray& controlPins) {
		SpeedControls temp(controlPins);
		temp.begin();
		return temp;
	}

	void SpeedControls::begin() {
		using namespace LocalLib::PwmDevices;

		for (int i = 0; i < m_motorControls.size(); ++i) {
			m_motorControls[i].controller = MotorESC::create(m_motorControls[i].pin);
		}
	}

	void SpeedControls::uploadSpeedCfg(MotorSpeedCfg& motorLevels) {
		m_motorControls[0].controller.setLevel((uint16_t)((motorLevels >> MOTOR_0) & 8191));
		m_motorControls[1].controller.setLevel((uint16_t)((motorLevels >> MOTOR_1) & 8191));
		m_motorControls[2].controller.setLevel((uint16_t)((motorLevels >> MOTOR_2) & 8191));
		m_motorControls[3].controller.setLevel((uint16_t)((motorLevels >> MOTOR_3) & 8191));

		uint16_t val0 = (uint16_t)((motorLevels >> MOTOR_0) & 8191);
		uint16_t val1 = (uint16_t)((motorLevels >> MOTOR_1) & 8191);
		uint16_t val2 = (uint16_t)((motorLevels >> MOTOR_2) & 8191);
		uint16_t val3 = (uint16_t)((motorLevels >> MOTOR_3) & 8191);

		std::cout << "Motor 0: " << val0 << '\n';
		std::cout << "Motor 1: " << val1 << '\n';
		std::cout << "Motor 2: " << val2 << '\n';
		std::cout << "Motor 3: " << val3 << "\n\n";

		motorLevels = 0;
	}

	void configureMotorSpeed(MotorSpeedCfg* config, Motor selectMotor, const uint16_t& speed) {
		*config |= ((uint64_t)speed << selectMotor);
		std::cout << "Config: " << *config << "\n\n";
	}
} // namespace LocalLib::Quad
