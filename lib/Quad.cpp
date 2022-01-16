#include "Quad.hpp"
#include "Helpers/Macros.hpp"

using namespace LocalLib;
using namespace LocalLib::PwmDevices;

namespace LocalLib::Quad {
	Controls::Controls(std::array<gpioPin_t, 4>&& pinsArray) : m_pinsArray(pinsArray) {
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
	void Controls::input(int16_t&& thrust, int16_t&& yaw, int16_t&& pitch, int16_t&& roll) {
		// DEBUG_RUN(std::cout << "Quad.cpp: input(): INFO: data moved\n";)

		// parsing the speed from input to each of the quad's motors
		float motorSpeed[4] = {0, 0, 0, 0};

		motorSpeed[0] = (thrust * spdAlloc[Z_TRANS]) + ((yaw - m_offset) * spdAlloc[Z_ROT]) +
						((pitch - m_offset) * spdAlloc[XY_ROT]) + ((roll - m_offset) * spdAlloc[XY_ROT]);
		motorSpeed[1] = (thrust * spdAlloc[Z_TRANS]) - ((yaw - m_offset) * spdAlloc[Z_ROT]) +
						((pitch - m_offset) * spdAlloc[XY_ROT]) - ((roll - m_offset) * spdAlloc[XY_ROT]);
		motorSpeed[2] = (thrust * spdAlloc[Z_TRANS]) + ((yaw - m_offset) * spdAlloc[Z_ROT]) -
						((pitch - m_offset) * spdAlloc[XY_ROT]) - ((roll - m_offset) * spdAlloc[XY_ROT]);
		motorSpeed[3] = (thrust * spdAlloc[Z_TRANS]) - ((yaw - m_offset) * spdAlloc[Z_ROT]) -
						((pitch - m_offset) * spdAlloc[XY_ROT]) + ((roll - m_offset) * spdAlloc[XY_ROT]);

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
		// DEBUG_RUN(std::cout << "Quad.cpp: input(): INFO: const ref data\n";)

		// parsing the speed from input to each of the quad's motors
		float motorSpeed[4] = {0, 0, 0, 0};

		motorSpeed[0] = (thrust * spdAlloc[Z_TRANS]) + ((yaw - m_offset) * spdAlloc[Z_ROT]) +
						((pitch - m_offset) * spdAlloc[XY_ROT]) + ((roll - m_offset) * spdAlloc[XY_ROT]);
		motorSpeed[1] = (thrust * spdAlloc[Z_TRANS]) - ((yaw - m_offset) * spdAlloc[Z_ROT]) +
						((pitch - m_offset) * spdAlloc[XY_ROT]) - ((roll - m_offset) * spdAlloc[XY_ROT]);
		motorSpeed[2] = (thrust * spdAlloc[Z_TRANS]) + ((yaw - m_offset) * spdAlloc[Z_ROT]) -
						((pitch - m_offset) * spdAlloc[XY_ROT]) - ((roll - m_offset) * spdAlloc[XY_ROT]);
		motorSpeed[3] = (thrust * spdAlloc[Z_TRANS]) - ((yaw - m_offset) * spdAlloc[Z_ROT]) -
						((pitch - m_offset) * spdAlloc[XY_ROT]) + ((roll - m_offset) * spdAlloc[XY_ROT]);

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
} // namespace LocalLib::Quad