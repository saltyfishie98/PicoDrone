#include "Helpers/Pico.hpp"

#include "pico/stdlib.h"
#include "hardware/adc.h"
#include <iostream>

#include "ErrMacros.hpp"
#include "Helpers/Macros.hpp"

namespace LocalLib::Helpers::Pico {
	AnalogReader::AnalogReader(const gpioPin_t& number) : m_pinNumber(number) {
		m_input = m_pinNumber - 26;
	}

	AnalogReader AnalogReader::create(const gpioPin_t& number) {
		AnalogReader temp(number);
		temp.begin();
		return temp;
	}

	void AnalogReader::begin() {
		Predicate pinMustEqualThisNum = (m_pinNumber == 26 || m_pinNumber == 27 || m_pinNumber == 28);

		CHECK_ERROR(pinMustEqualThisNum, ERR_ADC, ERR_DT_ADC_INVALID_PIN, {
			adc_init();
			adc_gpio_init(m_pinNumber);
		});
	}

	uint16_t AnalogReader::read() {
		// DEBUG_RUN(std::cout << "Pico.cpp: adc_read: INFO: level: " << adc_read() << '\n';)
		adc_select_input(m_input);
		DEBUG_RUN(m_val = adc_read();)
		return adc_read();
	}

	void AnalogReader::debugPrint() const {
		DEBUG_RUN(std::cout << "Pico.cpp: debugPrint: INFO: " << m_val << '\n';)
	}

} // namespace LocalLib::Helpers::Pico

namespace LocalLib::Helpers::Pico::Mutex {

	Mutex::~Mutex() {
		unlock();
	}

	Mutex Mutex::create() {
		Mutex temp;
		temp.begin();
		return temp;
	}

	void Mutex::begin() {
		if (Mutex::notInit) {
			mutex_init(&m_mtx);
			Mutex::notInit = false;
		}
	}

	void Mutex::lock() {
		mutex_enter_blocking(&m_mtx);
		DEBUG_RUN({
			sleep_ms(100);
			std::cout << "\n\n=========================== entered mutex ===========================\n\n";
		})
	}

	void Mutex::unlock() {
		mutex_exit(&m_mtx);
		DEBUG_RUN({
			std::cout << "\n\n=========================== exit mutex ===========================\n\n";
			sleep_ms(100);
		})
	}

	uint32_t* mtxIdPtr = nullptr;
	bool Mutex::entered() {
		return mutex_try_enter(&m_mtx, mtxIdPtr);
	}
} // namespace LocalLib::Helpers::Pico::Mutex