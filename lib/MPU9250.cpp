#include "mpu9250.hpp"
#include <stdio.h>

namespace LocalLib {
	mpu9250 mpu9250::create(uint&& miso, uint&& cs, uint&& sck, uint&& mosi) {
		mpu9250 temp(std::move(miso), std::move(cs), std::move(sck), std::move(mosi));
		temp.reset();
		temp.calibrateGyro(100);
		return temp;
	}

	mpu9250::mpu9250(uint&& miso, uint&& cs, uint&& sck, uint&& mosi) {
		m_spi = Pico::SPI::create(std::move(miso), std::move(cs), std::move(sck), std::move(mosi));
	}

	void mpu9250::reset() {
		uint8_t reg[2] = {0x6B, 0x00};
		m_spi.writeRegister(reg, 2);
	}

	void mpu9250::calibrateGyro(uint8_t&& numLoop) {
		mpu9250::Vec3 temp;

		for (int i = 0; i < numLoop; i++) {
			temp = rawGyro();
			m_gyroCal.X += temp.X;
			m_gyroCal.Y += temp.Y;
			m_gyroCal.Z += temp.Z;
			printf("gyrocal0: %d, gyrocal1: %d, gyrocal2: %d\n", m_gyroCal.X / i, m_gyroCal.Y / i, m_gyroCal.Z / i);
		}
		m_gyroCal.X /= numLoop;
		m_gyroCal.Y /= numLoop;
		m_gyroCal.Z /= numLoop;
	}

	mpu9250::Vec3 mpu9250::rawAccel() {
		mpu9250::Vec3 out;

		uint8_t data[6];
		m_spi.readRegister(0x3B, data, 6);

		out.X = (data[1] << 8 | data[2]);
		out.Y = (data[2] << 8 | data[3]);
		out.Z = (data[4] << 8 | data[5]);

		return out;
	}

	mpu9250::Vec3 mpu9250::rawGyro() {
		mpu9250::Vec3 out;

		uint8_t data[6];
		m_spi.readRegister(0x43, data, 6);

		out.X = (data[1] << 8 | data[2]);
		out.Y = (data[2] << 8 | data[3]);
		out.Z = (data[4] << 8 | data[5]);

		return out;
	}
} // namespace LocalLib