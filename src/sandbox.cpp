#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "PwmDevices/PwmDevices.hpp"
#include "Helpers/Pico.hpp"
#include "Helpers/Macros.hpp"
#include "Quad.hpp"
#include <iostream>

void sandbox() {
	using namespace LocalLib;
	using namespace LocalLib::Helpers;

	Pico::AnalogReader thrust = Pico::AnalogReader::create(26);
	Pico::AnalogReader yaw = Pico::AnalogReader::create(27);
	Pico::AnalogReader pitch = Pico::AnalogReader::create(28);

	PwmDevices::GeneralDevices motor0 = PwmDevices::GeneralDevices::create(50, 4);
	PwmDevices::GeneralDevices motor1 = PwmDevices::GeneralDevices::create(50, 5);
	PwmDevices::GeneralDevices motor2 = PwmDevices::GeneralDevices::create(50, 6);

	while (true) {
		uint64_t motor_0 = thrust.read() + yaw.read() + pitch.read();
		uint64_t motor_1 = thrust.read() - yaw.read() + pitch.read();
		uint64_t motor_2 = thrust.read() + yaw.read() - pitch.read();

		motor0.setLevel(motor_0);
		motor1.setLevel(motor_1);
		motor2.setLevel(motor_2);

		DEBUG_RUN(std::cout << '\n';)
	}
}