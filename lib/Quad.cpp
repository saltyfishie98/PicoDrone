#include "Quad.hpp"
#include "Helpers/Macros.hpp"

using namespace LocalLib;

namespace LocalLib::Quad {
	Controls::Controls(std::array<gpioPin_t, 4>&& pinsArray) : m_pinsArray(pinsArray) {
		m_motor0 = PwmDevices::MotorESC::create(m_pinsArray[0]);
		m_motor1 = PwmDevices::MotorESC::create(m_pinsArray[1]);
		m_motor2 = PwmDevices::MotorESC::create(m_pinsArray[2]);
		m_motor3 = PwmDevices::MotorESC::create(m_pinsArray[3]);
	}

	Controls Controls::create(std::array<gpioPin_t, 4>&& pinsArray) {
		Controls temp = Controls(std::move(pinsArray));
		temp.begin();
		return temp;
	}

	void Controls::begin() {}

	void Controls::input(uint16_t&& thrust, uint16_t&& yaw, uint16_t&& pitch, uint16_t&& roll) {
		DEBUG_RUN(std::cout << "Quad.cpp: input(): INFO: data moved\n";)

		uint64_t motor_0 = thrust + yaw + pitch + roll;
		uint64_t motor_1 = thrust - yaw + pitch - roll;
		uint64_t motor_2 = thrust + yaw - pitch - roll;
		uint64_t motor_3 = thrust - yaw - pitch + roll;

		m_motor0.setLevel(motor_0);
		m_motor1.setLevel(motor_1);
		m_motor2.setLevel(motor_2);
		m_motor3.setLevel(motor_3);
	}

	void Controls::input(const uint16_t& thrust, const uint16_t& yaw, const uint16_t& pitch, const uint16_t& roll) {
		DEBUG_RUN(std::cout << "Quad.cpp: input(): INFO: const ref data\n";)

		uint64_t speeds = 0;

		uint64_t motor_0 = thrust + yaw + pitch + roll;
		uint64_t motor_1 = thrust - yaw + pitch - roll;
		uint64_t motor_2 = thrust + yaw - pitch - roll;
		uint64_t motor_3 = thrust - yaw - pitch + roll;

		m_motor0.setLevel(motor_0);
		m_motor1.setLevel(motor_1);
		m_motor2.setLevel(motor_2);
		m_motor3.setLevel(motor_3);
	}
} // namespace LocalLib::Quad