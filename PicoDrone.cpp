#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/adc.h"
#include "hardware/clocks.h"

#include <iostream>
#include <cmath>

float clockDiv = 64;
float wrap = 39062;

void setMillis(int servoPin, float percent) {
	float millis = percent * (2400.f - 400.f) / 1 + 400.f;
	std::cout << "millis: " << millis << "\n\n";
	pwm_set_gpio_level(servoPin, (millis / 20000.f) * wrap);
}

void setServo(int servoPin) {
	gpio_set_function(servoPin, GPIO_FUNC_PWM);
	uint slice_num = pwm_gpio_to_slice_num(servoPin);

	pwm_config config = pwm_get_default_config();
	uint64_t clockspeed = clock_get_hz(clk_sys);
	clockDiv = 64;
	wrap = 39062;

	while (clockspeed / clockDiv / 50 > 65535 && clockDiv < 256) {
		clockDiv += 64;
	}

	wrap = clockspeed / clockDiv / 50;

	pwm_config_set_clkdiv(&config, clockDiv);
	pwm_config_set_wrap(&config, wrap);

	pwm_init(slice_num, &config, true);
}

int main() {
	stdio_init_all();

	adc_init();

	const uint8_t analogInputPin = 27;
	adc_gpio_init(analogInputPin);
	adc_select_input(analogInputPin - 26);

	const int servoPin = 4;
	setServo(servoPin);

	while (true) {
		float potVal = adc_read() / 4095.f;
		std::cout << "potVal%: " << potVal << "\n";

		setMillis(servoPin, potVal);
	}
}
