#include "Helpers/Pico.hpp"

#include "pico/stdlib.h"
#include "hardware/adc.h"
#include <iostream>

#include "ErrMacros.hpp"
#include "Helpers/Macros.hpp"

namespace LocalLib::Pico {
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

} // namespace LocalLib::Pico

namespace LocalLib::Pico {
	SPI::SPI(uint&& miso, uint&& cs, uint&& sck, uint&& mosi) : m_miso(miso), m_cs(cs), m_sck(sck), m_mosi(mosi) {}

	void SPI::begin() {
		spi_init(SPI_PORT, 500 * 1000);
		gpio_set_function(m_miso, GPIO_FUNC_SPI);
		gpio_set_function(m_sck, GPIO_FUNC_SPI);
		gpio_set_function(m_mosi, GPIO_FUNC_SPI);

		// Chip select is active-low, so we'll initialise it to a driven-high state
		gpio_init(m_cs);
		gpio_set_dir(m_cs, GPIO_OUT);
		gpio_put(m_cs, 1);
	}

	SPI SPI::create(uint&& miso, uint&& cs, uint&& sck, uint&& mosi) {
		SPI temp(std::move(miso), std::move(cs), std::move(sck), std::move(mosi));
		temp.begin();
		return temp;
	}

	void SPI::csSelect() {
		asm volatile("nop \n nop \n nop");
		gpio_put(m_cs, 0); // Active low
		asm volatile("nop \n nop \n nop");
	}

	void SPI::csDeselect() {
		asm volatile("nop \n nop \n nop");
		gpio_put(m_cs, 1);
		asm volatile("nop \n nop \n nop");
	}

	void SPI::writeRegister(uint8_t* buffer, std::size_t len) noexcept {
		csSelect();
		spi_write_blocking(SPI_PORT, buffer, len);
		csDeselect();
	}

	void SPI::readRegister(uint8_t&& reg, uint8_t* buffer, std::size_t len) noexcept {
		reg |= 0x80;
		csSelect();
		spi_write_blocking(SPI_PORT, buffer, len);
		sleep_ms(10);
		spi_read_blocking(SPI_PORT, 0, buffer, len);
		csDeselect();
		sleep_ms(10);
	}

} // namespace LocalLib::Pico

namespace LocalLib::Pico::Mutex {

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
} // namespace LocalLib::Pico::Mutex