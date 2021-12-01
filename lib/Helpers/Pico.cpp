#include "Helpers/Pico.hpp"

#include "pico/stdlib.h"
#include "hardware/adc.h"
#include <iostream>

#include "../ErrMacros.hpp"
#include "Helpers/Macros.hpp"

namespace LocalLib::Helpers::Pico {
	AnalogReader::AnalogReader(const gpioPin_t& number) : m_pinNumber(number) {}

	AnalogReader AnalogReader::factory(const gpioPin_t& number) {
		AnalogReader temp(number);
		temp.begin();
		return temp;
	}

	void AnalogReader::begin() {
		Predicate pinMustEqualThisNum =
		  (m_pinNumber == 26 || m_pinNumber == 27 || m_pinNumber == 28);

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

namespace LocalLib::Helpers::Pico::Mutex {
	uint32_t* mtxIdPtr = nullptr;

	BasicMutex::BasicMutex() {}

	BasicMutex::~BasicMutex() {
		unlock();
	}

	void BasicMutex::begin() {
		if (IMutex::notInit) {
			mutex_init(&m_mtx);
			IMutex::notInit = false;
		}
	}

	void BasicMutex::lock() {
		mutex_enter_blocking(&m_mtx);
		DEBUG_RUN({
			sleep_ms(100);
			std::cout
			  << "\n\n=========================== entered mutex ===========================\n\n";
		})
	}

	void BasicMutex::unlock() {
		mutex_exit(&m_mtx);
		DEBUG_RUN({
			std::cout
			  << "\n\n=========================== exit mutex ===========================\n\n";
			sleep_ms(100);
		})
	}

	void BasicMutex::runIfOwned(const VoidCallback& thisStdFunction) {
		if (mutex_try_enter(&m_mtx, mtxIdPtr)) {
			DEBUG_RUN({
				sleep_ms(100);
				std::cout << "\n\n=========================== entered mutex "
							 "===========================\n\n";
			})
			thisStdFunction();
			unlock();
		}
	}

} // namespace LocalLib::Helpers::Pico::Mutex