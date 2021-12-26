#include "pico/stdlib.h"
#include "hardware/adc.h"
#include <iostream>

void sandbox() {
	adc_init();

	adc_gpio_init(26);
	adc_gpio_init(27);
	adc_gpio_init(28);

	while (true) {
		adc_select_input(0);
		uint16_t out = adc_read();
		if (out > 4095)
			out = 4095;
		std::cout << adc_read() << '\n';

		adc_select_input(1);
		out = adc_read();
		if (out > 4095)
			out = 4095;
		std::cout << adc_read() << '\n';

		adc_select_input(2);
		out = adc_read();
		if (out > 4095)
			out = 4095;
		std::cout << adc_read() << "\n\n";
	}
}