#include "Quad.hpp"
#include "Helpers/Macros.hpp"

using namespace PicoPilot;
using namespace PicoPilot::PwmDevices;

namespace PicoPilot::Quad {
	Controls::Controls(std::array<Pico::gpioPin_t, 4>&& pinsArray) : m_pinsArray(pinsArray) {
		m_motors = {
		  PwmDevices::MotorESC::create(m_pinsArray[0]),
		  PwmDevices::MotorESC::create(m_pinsArray[1]),
		  PwmDevices::MotorESC::create(m_pinsArray[2]),
		  PwmDevices::MotorESC::create(m_pinsArray[3]),
		};
	}

	void Controls::begin() {}

	/**
	 * @brief Factory method to create an instance of Quad::Controls
	 *
	 * @param pinsArray The number of the 4 pins used for outputing the pwm signals
	 * @return Controls
	 */
	Controls Controls::create(std::array<Pico::gpioPin_t, 4>&& pinsArray) {
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
	void Controls::input(int16_t&& thrust, int16_t&& yaw, int16_t&& pitch, int16_t&& roll) {
		// parsing the speed from input to each of the quad's motors
		float motorSpeed[4] = {0, 0, 0, 0};

		int16_t m_thrust = (thrust * spdAlloc[Z_TRANS]);

		if (m_thrust > 170) {
			int16_t m_yaw = (yaw - m_offset) * spdAlloc[Z_ROT];
			int16_t m_pitch = (pitch - m_offset) * spdAlloc[XY_ROT];
			int16_t m_roll = (roll - m_offset) * spdAlloc[XY_ROT];

			motorSpeed[0] = m_thrust + m_yaw + m_pitch + m_roll;
			motorSpeed[1] = m_thrust - m_yaw + m_pitch - m_roll;
			motorSpeed[2] = m_thrust + m_yaw - m_pitch - m_roll;
			motorSpeed[3] = m_thrust - m_yaw - m_pitch + m_roll;

		} else {
			motorSpeed[0] = m_thrust;
			motorSpeed[1] = m_thrust;
			motorSpeed[2] = m_thrust;
			motorSpeed[3] = m_thrust;
		}

		for (auto i = 0; i < m_motors.size(); ++i) {
			if (motorSpeed[i] <= 0) {
				motorSpeed[i] = 0;
			}
			m_motors[i].setRangedLevel(motorSpeed[i]);
		}
	}

	/**
	 * @brief Inputs for controlling the motion of the Quad (NOTE: smaller than wrap value for 50Hz)
	 *
	 * @param thrust value to set the quad's thrust
	 * @param yaw value to set the quad's yaw
	 * @param pitch value to set the quad's	pitch
	 * @param roll value to set the quad's roll
	 */
	void Controls::input(const int16_t& thrust, const int16_t& yaw, const int16_t& pitch, const int16_t& roll) {
		// parsing the speed from input to each of the quad's motors
		float motorSpeed[4] = {0, 0, 0, 0};

		int16_t m_thrust = (thrust * spdAlloc[Z_TRANS]);

		if (m_thrust > 170) {
			int16_t m_yaw = (yaw - m_offset) * spdAlloc[Z_ROT];
			int16_t m_pitch = (pitch - m_offset) * spdAlloc[XY_ROT];
			int16_t m_roll = (roll - m_offset) * spdAlloc[XY_ROT];

			motorSpeed[0] = m_thrust + m_yaw + m_pitch + m_roll;
			motorSpeed[1] = m_thrust - m_yaw + m_pitch - m_roll;
			motorSpeed[2] = m_thrust + m_yaw - m_pitch - m_roll;
			motorSpeed[3] = m_thrust - m_yaw - m_pitch + m_roll;

		} else {
			motorSpeed[0] = m_thrust;
			motorSpeed[1] = m_thrust;
			motorSpeed[2] = m_thrust;
			motorSpeed[3] = m_thrust;
		}

		for (auto i = 0; i < m_motors.size(); ++i) {
			if (motorSpeed[i] <= 0) {
				motorSpeed[i] = 0;
			}
			m_motors[i].setRangedLevel(motorSpeed[i]);
		}
	}

	void Controls::debugPrint() const {
		for (auto& motor : m_motors) {
			motor.debugPrint();
		}
	}
} // namespace PicoPilot::Quad