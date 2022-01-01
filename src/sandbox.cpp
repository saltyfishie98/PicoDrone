#include <iostream>
#include <stdio.h>
#include "hardware/pwm.h"
#include "hardware/clocks.h"
#include "pico/stdlib.h"

#include "Helpers/Pico.hpp"
#include "Helpers/Arduino.hpp"
#include "PwmDevices/PwmDevices.hpp"

void sandbox() {
	using namespace LocalLib::Helpers;
	using namespace LocalLib;

	Pico::AnalogReader pot0 = Pico::AnalogReader::create(28);
	PwmDevices::MotorESC led = PwmDevices::MotorESC::create(2);

	while (1) {
		led.setRangedLevel(pot0.read());
	}
}
