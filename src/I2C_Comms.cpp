#include "I2C/Comms.hpp"

namespace PicoPilot::I2C {
	Comms::Comms(Comms&& other) {
		m_devAddr = other.m_devAddr;
	}

	Comms& Comms::operator=(Comms&& other) {
		if (this != &other) {
			m_devAddr = other.m_devAddr;
		}

		return *this;
	}

	Comms::Comms(uint8_t deviceAddress, i2c_inst_t* port, Pico::gpioPin_t sda, Pico::gpioPin_t scl, uint32_t baudrate)
	  : m_devAddr(deviceAddress), m_port(port), m_sda(sda), m_scl(scl), m_baudrate(baudrate) {}

	Comms
	  Comms::create(uint8_t deviceAddress, i2c_inst_t* port, Pico::gpioPin_t sda, Pico::gpioPin_t scl, uint32_t baudrate) {
		Comms temp(deviceAddress, port, sda, scl, baudrate);
		temp.begin();
		return temp;
	}

	void Comms::begin() {
		i2c_init(m_port, m_baudrate);

		gpio_set_function(m_sda, GPIO_FUNC_I2C);
		gpio_set_function(m_scl, GPIO_FUNC_I2C);
		gpio_pull_up(m_sda);
		gpio_pull_up(m_scl);
	}

	bool Comms::connected() {
		uint8_t temp = 0;
		readByte(0x75, temp);

		return temp == 0x68;
	}

	int8_t Comms::readBytes(uint8_t regAddr, uint8_t length, uint8_t* data, uint32_t timeout) {
		int8_t count = 0;

		i2c_write_blocking(m_port, m_devAddr, &regAddr, 1, true);
		count = i2c_read_blocking(m_port, m_devAddr, data, length, false);

		return count;
	}

	bool Comms::writeBytes(uint8_t regAddr, uint8_t length, uint8_t* data) {
		uint8_t status = 0;
		uint8_t data_buf[length + 1];

		data_buf[0] = regAddr;
		for (int i = 0; i < length; i++) {
			data_buf[i + 1] = data[i];
		}
		status = i2c_write_blocking(m_port, m_devAddr, data_buf, length + 1, false);

		return status;
	}

	int8_t Comms::readByte(uint8_t regAddr, uint8_t& data, uint32_t timeout) {
		return readBytes(regAddr, 1, &data, timeout);
	}

	bool Comms::writeByte(uint8_t regAddr, uint8_t& data) {
		return writeBytes(regAddr, 1, &data);
	}

	bool Comms::writeBit(uint8_t regAddr, uint8_t bitNum, uint8_t data) {
		uint8_t b;
		readByte(regAddr, b);
		b = (data != 0) ? (b | (1 << bitNum)) : (b & ~(1 << bitNum));
		return writeByte(regAddr, b);
	}

} // namespace PicoPilot::I2C