#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"
#include "hardware/adc.h"

#include <iostream>
#include <cmath>

#include "lib/Helpers.hpp"
#include "lib/Servo.hpp"

using namespace LocalLib;

int main() {
	stdio_init_all();

	adc_init();

	const uint8_t analogInputPin = 27;
	adc_gpio_init(analogInputPin);
	adc_select_input(analogInputPin - 26);

	Servo servo0(4);

	while (true) {
		float potVal = adc_read() / 4095.f;
		std::cout << "potVal%: " << potVal << "\n";

		servo0.setPercent(potVal);
	}
}
