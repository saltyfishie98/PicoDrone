#include "Namespace_Pico.hpp"

#include "hardware/adc.h"
#include <iostream>

// clang-format off
#define CHECK_ADC_PIN(pin_num_variable, error_code, run_this) 	\
	if (pin_num_variable == 26 || pin_num_variable == 27 || pin_num_variable == 28) { \
		run_this \
	} else { \
		std::cout << "Error Code: " << error_code << "\n"; \
		std::abort(); \
	}
// clang-format on

namespace LocalLib::Helpers::Pico {
	AnalogReader::AnalogReader(const GpioPin& number) : m_pinNumber(number) {
		CHECK_ADC_PIN(m_pinNumber, 2, {
			adc_init();
			adc_gpio_init(m_pinNumber);
			adc_select_input(m_pinNumber - 26);
		});
	}

	uint16_t AnalogReader::read() {
		return adc_read();
	}

} // namespace LocalLib::Helpers::Pico
