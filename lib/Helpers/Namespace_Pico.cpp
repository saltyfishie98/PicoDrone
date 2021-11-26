#include "Namespace_Pico.hpp"

#include "pico/stdlib.h"
#include "hardware/adc.h"
#include <iostream>

#include "../ErrorHandler.hpp"

namespace LocalLib::Helpers::Pico {
	AnalogReader::AnalogReader(const GpioPin& number) : m_pinNumber(number) {}

	void AnalogReader::begin() {
		Predicate pinMustEqualThisNum = (m_pinNumber == 26 || m_pinNumber == 27 || m_pinNumber == 28);

		CHECK_ERROR(pinMustEqualThisNum, ERR_ADC, ERR_DT_ADC_INVALID_PIN, {
			adc_init();
			adc_gpio_init(m_pinNumber);
			adc_select_input(m_pinNumber - 26);
		});
	}

	uint16_t AnalogReader::read() {
		return adc_read();
	}

} // namespace LocalLib::Helpers::Pico
