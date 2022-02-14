#include "Mpu9250.hpp"

#include <stdio.h>
#include <cmath>
#include "hardware/clocks.h"
#include "Helpers/Macros.hpp"
#include "Helpers/Misc.hpp"

namespace PicoPilot {
	using namespace Misc;
	using namespace Pico;

	Mpu9250::Mpu9250(spi_inst_t* port, SPI::Pins&& gpioPins) {
		SPI::m_port = port;
		SPI::m_pins = std::move(gpioPins);
	}

	Mpu9250 Mpu9250::create(spi_inst_t* port, SPI::Pins&& gpioPins) {
		Mpu9250 temp(port, std::move(gpioPins));
		temp.begin();
		temp.getMpuOffsets();
		return temp;
	}

	void Mpu9250::begin() noexcept {
		SPI::begin();
		reset();

		SPI::readRegs(0x75, &data, 1);
		sleep_ms(10);

		if (data != 0x71) {
			DEBUG_RUN(printf("Mpu9250 begin error!\n");)
			while (1) {}
		}

		setGyroSens();
		setAccelSens();

		// // set DLPF_CFG
		// SPI::readRegs(0x1A, &data, 1);
		// data |= 4 << 0;
		// uint8_t dlpfCfgBuf[] = {0x1A, data};
		// SPI::writeRegs(dlpfCfgBuf, 2);

		// // Read and set A_DLPF_CFG and ACCEL_FCHOICE to use A_DLPF_CFG
		// SPI::readRegs(0x1D, &data, 1);
		// data |= 6 << 0;
		// data |= 0 << 3;
		// uint8_t accelDlpfCfgBuf[] = {0x1C, data};
		// SPI::writeRegs(accelDlpfCfgBuf, 2);
	}

	void Mpu9250::reset() noexcept {
		// uint8_t data = 0;
		// readRegs(0x6B, &data, 1);
		// data |= 1 << 7;
		// uint8_t hResetBuf[] = {0x6B, data};
		// SPI::writeRegs(hResetBuf, 2);
		// sleep_ms(5000);
		// abort();

		uint8_t buf[] = {0x6B, 0x00};
		SPI::writeRegs(buf, 2);
	}

	Mpu9250::QuadVec3 Mpu9250::getRawMilliAccel() {
		uint8_t buffer[6] = {0, 0, 0, 0, 0, 0};
		static QuadVec3 rawAccel;

		SPI::readRegs(0x3B, buffer, 6);

		rawAccel.X = (buffer[0] << 8 | buffer[1]);
		rawAccel.Y = (buffer[2] << 8 | buffer[3]);
		rawAccel.Z = (buffer[4] << 8 | buffer[5]);

		rawAccel.X = ((double)rawAccel.X / 2048.0) * 1000;
		rawAccel.Y = ((double)rawAccel.Y / 2048.0) * 1000;
		rawAccel.Z = ((double)rawAccel.Z / 2048.0) * 1000;

		return rawAccel;
	}

	Mpu9250::QuadVec3 Mpu9250::getRawGyro() {
		uint8_t buffer[6] = {0, 0, 0, 0, 0, 0};
		static QuadVec3 rawGyro;

		SPI::readRegs(0x43, buffer, 6);

		rawGyro.X = (buffer[0] << 8 | buffer[1]);
		rawGyro.Y = (buffer[2] << 8 | buffer[3]);
		rawGyro.Z = (buffer[4] << 8 | buffer[5]);

		// https://github.com/MarkSherstan/MPU-6050-9250-I2C-CompFilter/blob/master/Arduino/main/main.ino
		rawGyro.X = (double)rawGyro.X / 16.4;
		rawGyro.Y = (double)rawGyro.Y / 16.4;
		rawGyro.Z = (double)rawGyro.Z / 16.4;

		return rawGyro;
	}

	void Mpu9250::getMpuOffsets() {
		uint32_t count = 0;

		while (count < 12000) {
			auto gyro = getRawGyro();
			auto milliAccel = getRawMilliAccel();

			m_gyroOffset.X += gyro.X;
			m_gyroOffset.Y += gyro.Y;
			m_gyroOffset.Z += gyro.Z;

			m_accelOffset.X += milliAccel.X;
			m_accelOffset.Y += milliAccel.Y;
			m_accelOffset.Z += milliAccel.Z;

			++count;
		}

		m_gyroOffset.X /= 12000.f;
		m_gyroOffset.Y /= 12000.f;
		m_gyroOffset.Z /= 12000.f;

		m_accelOffset.X /= 12000.f;
		m_accelOffset.Y /= 12000.f;
		m_accelOffset.Z /= 12000.f;
	}

	Mpu9250::QuadVec3 Mpu9250::gyroVals() {
		static QuadVec3 out;
		out = getRawGyro();

		// Correct the outputs with the calculated error values
		out.X = out.X - m_gyroOffset.X;
		out.Y = out.Y - m_gyroOffset.Y;
		out.Z = out.Z - m_gyroOffset.Z;

		// LP filter gyro data
		float B_gyro = 0.1f; // 0.13 sets cutoff just past 80Hz for about 3000Hz loop rate
		out.X = (1.0f - B_gyro) * m_prevGyro.X + B_gyro * out.X;
		out.Y = (1.0f - B_gyro) * m_prevGyro.Y + B_gyro * out.Y;
		out.Z = (1.0f - B_gyro) * m_prevGyro.Z + B_gyro * out.Z;

		m_prevGyro.X = out.X;
		m_prevGyro.Y = out.Y;
		m_prevGyro.Z = out.Z;

		return out;
	}

	Mpu9250::QuadVec3 Mpu9250::accelMilliVals() {
		using namespace Misc;

		static QuadVec3 out;

		out = getRawMilliAccel();

		// Correct the outputs with the calculated error values
		out.X = out.X - m_accelOffset.X;
		out.Y = out.Y - m_accelOffset.Y;
		out.Z = out.Z - m_accelOffset.Z;

		// LP filter gyro data
		float B_gyro = 0.14f; // 0.13 sets cutoff just past 80Hz for about 3000Hz loop rate
		out.X = (1.0f - B_gyro) * m_prevAccel.X + B_gyro * out.X;
		out.Y = (1.0f - B_gyro) * m_prevAccel.Y + B_gyro * out.Y;
		out.Z = (1.0f - B_gyro) * m_prevAccel.Z + B_gyro * out.Z;

		m_prevAccel.X = out.X;
		m_prevAccel.Y = out.Y;
		m_prevAccel.Z = out.Z;

		out.Z += 1000;

		return out;
	}

	void Mpu9250::setGyroSens() {
		SPI::readRegs(0x1B, &data, 1);
		data |= 0b11 << 3;
		uint8_t gyroSen[] = {0x1B, data};
		SPI::writeRegs(gyroSen, 2);
	}

	void Mpu9250::setAccelSens() {
		SPI::readRegs(0x1C, &data, 1);
		data |= 0b11 << 3;
		uint8_t accelSen[] = {0x1C, data};
		SPI::writeRegs(accelSen, 2);
	}

	void Mpu9250::checkSettings() {
		uint8_t data = 0;
		SPI::readRegs(0x1A, &data, 1);
		printf("DLPF_CFG = %d\n", data & 0b111);

		SPI::readRegs(0x1B, &data, 1);
		printf("FCHOICE_B = %d\n\n", data & 0b11);

		SPI::readRegs(0x1C, &data, 1);
		printf("ACCEL_DLPF_CFG = %d\n", data & 0b111);

		SPI::readRegs(0x1D, &data, 1);
		printf("ACCEL_FCHOICE_B = %d\n\n", data & 0b11);

		SPI::readRegs(0x1B, &data, 1);
		printf("GYRO_SEN = %d\n", (data >> 3) & 0b11);

		SPI::readRegs(0x1C, &data, 1);
		printf("ACCEL_SEN = %d\n\n", (data >> 3) & 0b111);
	}

	void Mpu9250::checkMpuVals() {
		QuadVec3 temp = gyroVals();
		printf("gyro values: X: %d, Y: %d, Z: %d\n", temp.X, temp.Y, temp.Z);

		temp = accelMilliVals();
		printf("accel values: X: %f, Y: %f, Z: %f\n\n", temp.X / 1000.f, temp.Y / 1000.f, temp.Z / 1000.f);
	}

} // namespace PicoPilot