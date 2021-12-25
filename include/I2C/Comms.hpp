#ifndef C__PROJECTS_PICO_PICODRONE_INCLUDE_I2C_I2C_HPP_
#define C__PROJECTS_PICO_PICODRONE_INCLUDE_I2C_I2C_HPP_

#include "pico/stdlib.h"
#include "hardware/i2c.h"

#include "../Types.hpp"

#define I2CDEV_DEFAULT_READ_TIMEOUT ((uint32_t)1000000)

namespace LocalLib::I2C {
	class Comms {
	  public:
		Comms(const Comms&) = delete;
		Comms& operator=(const Comms&) = delete;

		Comms(Comms&&) noexcept;
		Comms& operator=(Comms&&) noexcept;

		static Comms create(uint8_t deviceAddress, i2c_inst_t* port, gpioPin_t sda, gpioPin_t scl, uint32_t baudrate);

		bool connected();

		int8_t readBytes(uint8_t regAddr, uint8_t length, uint8_t* data, uint32_t timeout = I2CDEV_DEFAULT_READ_TIMEOUT);
		bool writeBytes(uint8_t regAddr, uint8_t length, uint8_t* data);

		int8_t readByte(uint8_t regAddr, uint8_t& data, uint32_t timeout = I2CDEV_DEFAULT_READ_TIMEOUT);
		bool writeByte(uint8_t regAddr, uint8_t& data);

		bool writeBit(uint8_t regAddr, uint8_t bitNum, uint8_t data);

	  private:
		Comms(uint8_t deviceAddress, i2c_inst_t* port, gpioPin_t sda, gpioPin_t scl, uint32_t baudrate) noexcept;

		void begin();

		uint8_t m_devAddr = 0;
		gpioPin_t m_sda = NULLPIN;
		gpioPin_t m_scl = NULLPIN;
		uint32_t m_baudrate = 0;
		i2c_inst_t* m_port;
	};
} // namespace LocalLib::I2C

#endif // C__PROJECTS_PICO_PICODRONE_INCLUDE_I2C_I2C_HPP_