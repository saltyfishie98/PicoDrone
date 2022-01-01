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

	void Controls::begin() {}

	/**
	 * @brief Factory method to create an instance of Quad::Controls
	 *
	 * @param pinsArray The number of the 4 pins used for outputing the pwm signals
	 * @return Controls
	 */
	Controls Controls::create(std::array<gpioPin_t, 4>&& pinsArray) {
		Controls temp = Controls(std::move(pinsArray));
		temp.begin();
		return temp;
	}

	/**
	 * @brief Inputs for controlling the motion of the Quad (NOTE: smaller than wrap value for 50Hz)
	 *
	 * @param thrust
	 * @param yaw
	 * @param pitch
	 * @param roll
	 */
	void Controls::input(uint16_t&& thrust, uint16_t&& yaw, uint16_t&& pitch, uint16_t&& roll) {
		DEBUG_RUN(std::cout << "Quad.cpp: input(): INFO: data moved\n";)

		// parsing the speed from input to each of the quad's motors
		uint64_t motor_0 = thrust + yaw + pitch + roll;
		uint64_t motor_1 = thrust - yaw + pitch - roll;
		uint64_t motor_2 = thrust + yaw - pitch - roll;
		uint64_t motor_3 = thrust - yaw - pitch + roll;

		m_motor0.setRangedLevel(motor_0);
		m_motor1.setRangedLevel(motor_1);
		m_motor2.setRangedLevel(motor_2);
		m_motor3.setRangedLevel(motor_3);
	}

	/**
	 * @brief Inputs for controlling the motion of the Quad (NOTE: smaller than wrap value for 50Hz)
	 *
	 * @param thrust value to set the quad's thrust
	 * @param yaw value to set the quad's yaw
	 * @param pitch value to set the quad's	pitch
	 * @param roll value to set the quad's roll
	 */
	void Controls::input(const uint16_t& thrust, const uint16_t& yaw, const uint16_t& pitch, const uint16_t& roll) {
		DEBUG_RUN(std::cout << "Quad.cpp: input(): INFO: const ref data\n";)

		uint64_t speeds = 0;

		uint64_t motor_0 = thrust + yaw + pitch + roll;
		uint64_t motor_1 = thrust - yaw + pitch - roll;
		uint64_t motor_2 = thrust + yaw - pitch - roll;
		uint64_t motor_3 = thrust - yaw - pitch + roll;

		m_motor0.setRangedLevel(motor_0);
		m_motor1.setRangedLevel(motor_1);
		m_motor2.setRangedLevel(motor_2);
		m_motor3.setRangedLevel(motor_3);
	}
} // namespace LocalLib::Quad