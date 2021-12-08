#include "I2C/I2CComms.hpp"

namespace LocalLib {
	I2CComms::I2CComms(I2CComms&& other) {
		m_devAddr = other.m_devAddr;
	}

	I2CComms& I2CComms::operator=(I2CComms&& other) {
		if (this != &other) {
			m_devAddr = other.m_devAddr;
		}

		return *this;
	}

	I2CComms::I2CComms(uint8_t deviceAddress, i2c_inst_t* port, gpioPin_t sda, gpioPin_t scl, uint32_t baudrate)
	  : m_devAddr(deviceAddress), m_port(port), m_sda(sda), m_scl(scl), m_baudrate(baudrate) {}

	I2CComms I2CComms::create(uint8_t deviceAddress, i2c_inst_t* port, gpioPin_t sda, gpioPin_t scl, uint32_t baudrate) {
		I2CComms temp(deviceAddress, port, sda, scl, baudrate);
		temp.begin();
		return temp;
	}

	void I2CComms::begin() {
		i2c_init(m_port, m_baudrate);

		gpio_set_function(m_sda, GPIO_FUNC_I2C);
		gpio_set_function(m_scl, GPIO_FUNC_I2C);
		gpio_pull_up(m_sda);
		gpio_pull_up(m_scl);
	}

	bool I2CComms::connected() {
		uint8_t temp = 0;
		readByte(0x75, temp);

		return temp == 0x68;
	}

	int8_t I2CComms::readBytes(uint8_t regAddr, uint8_t length, uint8_t* data, uint32_t timeout) {
		int8_t count = 0;

		i2c_write_blocking(m_port, m_devAddr, &regAddr, 1, true);
		count = i2c_read_blocking(m_port, m_devAddr, data, length, false);

		return count;
	}

	bool I2CComms::writeBytes(uint8_t regAddr, uint8_t length, uint8_t* data) {
		uint8_t status = 0;
		uint8_t data_buf[length + 1];

		data_buf[0] = regAddr;
		for (int i = 0; i < length; i++) {
			data_buf[i + 1] = data[i];
		}
		status = i2c_write_blocking(m_port, m_devAddr, data_buf, length + 1, false);

		return status;
	}

	int8_t I2CComms::readByte(uint8_t regAddr, uint8_t& data, uint32_t timeout) {
		return readBytes(regAddr, 1, &data, timeout);
	}

	bool I2CComms::writeByte(uint8_t regAddr, uint8_t& data) {
		return writeBytes(regAddr, 1, &data);
	}

	bool I2CComms::writeBit(uint8_t regAddr, uint8_t bitNum, uint8_t data) {
		uint8_t b;
		readByte(regAddr, b);
		b = (data != 0) ? (b | (1 << bitNum)) : (b & ~(1 << bitNum));
		return writeByte(regAddr, b);
	}

} // namespace LocalLib