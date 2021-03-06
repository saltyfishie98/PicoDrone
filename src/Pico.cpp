#include "Helpers/Pico.hpp"

#include "pico/stdlib.h"
#include "hardware/adc.h"

#include "ErrMacros.hpp"
#include "Helpers/Macros.hpp"

namespace Pico {
	AnalogReader::AnalogReader(const Pico::gpioPin_t& number) : m_pinNumber(number) {
		m_input = m_pinNumber - 26;
	}

	AnalogReader AnalogReader::create(const Pico::gpioPin_t& number) {
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
		adc_select_input(m_input);
		DEBUG_RUN(m_val = adc_read();)
		return adc_read();
	}

	void AnalogReader::debugPrint() const {
		DEBUG_RUN(printf("Pico.cpp: debugPrint: INFO: %d\n", (uint)m_val);)
	}

} // namespace Pico

namespace Pico {
	SPI::SPI(spi_inst_t* port, Pins&& gpioPins) : m_port(std::move(port)), m_pins(std::move(gpioPins)) {}

	SPI SPI::create(spi_inst_t* port, Pins&& pins) {
		SPI temp(port, std::move(pins));
		temp.begin();
		return temp;
	}

	void SPI::begin() {
		spi_init(m_port, 500 * 1000);
		gpio_set_function(m_pins.miso, GPIO_FUNC_SPI);
		gpio_set_function(m_pins.sck, GPIO_FUNC_SPI);
		gpio_set_function(m_pins.mosi, GPIO_FUNC_SPI);

		// Chip select is active-low, so we'll initialise it to a driven-high state
		gpio_init(m_pins.cs);
		gpio_set_dir(m_pins.cs, GPIO_OUT);
		gpio_put(m_pins.cs, 1);
	}

	void SPI::chipSelect() {
		asm volatile("nop \n nop \n nop");
		gpio_put(m_pins.cs, 0); // Active low
		asm volatile("nop \n nop \n nop");
	}

	void SPI::chipDeselect() {
		asm volatile("nop \n nop \n nop");
		gpio_put(m_pins.cs, 1);
		asm volatile("nop \n nop \n nop");
	}

	void SPI::readRegs(uint8_t reg, uint8_t* buf, uint16_t len) {
		// For this particular device, we send the device the register we want to read
		// first, then subsequently read from the device. The register is auto incrementing
		// so we don't need to keep sending the register we want, just the first.

		reg |= READ_BIT;
		chipSelect();
		spi_write_blocking(m_port, &reg, 1);
		spi_read_blocking(m_port, 0, buf, len);
		chipDeselect();
	}

	void SPI::writeRegs(const uint8_t* buf, size_t len) {
		chipSelect();
		spi_write_blocking(m_port, buf, len);
		chipDeselect();
	}
} // namespace Pico

namespace Pico::Mutex {

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
	}

	void Mutex::unlock() {
		mutex_exit(&m_mtx);
	}

	uint32_t* mtxIdPtr = nullptr;
	bool Mutex::entered() {
		return mutex_try_enter(&m_mtx, mtxIdPtr);
	}
} // namespace Pico::Mutex