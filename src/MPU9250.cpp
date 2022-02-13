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

		for (auto& config : gyroKalmanConfigs) {
			config.R = 100.f;
			config.H = 1.f;
			config.Q = 10.f;
			config.P = 0.f;
			config.UHat = 0.f;
			config.K = 0.f;
		}

		for (auto& config : accelKalmanConfigs) {
			config.R = 8000.f;
			config.H = 1.f;
			config.Q = 10.f;
			config.P = 0.f;
			config.UHat = 0.f;
			config.K = 0.f;
		}
	}

	Mpu9250 Mpu9250::create(spi_inst_t* port, SPI::Pins&& gpioPins, uint calibrationLoop) {
		Mpu9250 temp(port, std::move(gpioPins));
		temp.begin();
		temp.getMpuOffsets(calibrationLoop);
		return temp;
	}

	void Mpu9250::begin() noexcept {
		SPI::begin();
		reset();

		uint8_t data = 0;
		SPI::readRegs(0x75, &data, 1);
		sleep_ms(10);

		if (data != 0x71) {
			DEBUG_RUN(printf("Mpu9250 begin error!\n");)
			while (1) {}
		}

		// set DLPF_CFG
		SPI::readRegs(0x1A, &data, 1);
		data |= 4 << 0;
		uint8_t dlpfCfgBuf[] = {0x1A, data};
		SPI::writeRegs(dlpfCfgBuf, 2);

		// // set gyro range and set FCHOICE_B to use DLPF_CFG
		SPI::readRegs(0x1B, &data, 1);
		data |= 0b00 << 0;
		data |= 0b11 << 3;
		uint8_t gyroSen[] = {0x1B, data};
		SPI::writeRegs(gyroSen, 2);

		// set accel range
		SPI::readRegs(0x1C, &data, 1);
		data |= 0b11 << 3;
		uint8_t accelSen[] = {0x1C, data};
		SPI::writeRegs(accelSen, 2);

		// // Read and set A_DLPF_CFG and ACCEL_FCHOICE to use A_DLPF_CFG
		// SPI::readRegs(0x1D, &data, 1);
		// data |= 6 << 0;
		// data |= 0 << 3;
		// uint8_t accelDlpfCfgBuf[] = {0x1C, data};
		// SPI::writeRegs(accelDlpfCfgBuf, 2);

		getMpuOffsets();
	}

	void Mpu9250::reset() noexcept {
		// uint8_t data = 0;
		// readRegs(0x6B, &data, 1);
		// data |= 1 << 7;
		// uint8_t hResetBuf[] = {0x6B, data};
		// SPI::writeRegs(hResetBuf, 2);

		uint8_t buf[] = {0x6B, 0x00};
		SPI::writeRegs(buf, 2);
	}

	void Mpu9250::getMpuOffsets(uint loop) {
		Mpu9250::Vec3 tempGyro;
		Mpu9250::Vec3 tempAccel;

		sleep_ms(1000);
		for (int i = 0; i < loop; i++) {
			tempGyro = rawGyro();

			m_gyroCal.X += tempGyro.X;
			m_gyroCal.Y += tempGyro.Y;
			m_gyroCal.Z += tempGyro.Z;

			m_accelCal.X += tempAccel.X;
			m_accelCal.Y += tempAccel.Y;
			m_accelCal.Z += tempAccel.Z;
		}

		m_gyroCal.X /= loop;
		m_gyroCal.Y /= loop;
		m_gyroCal.Z /= loop;

		m_accelCal.X /= loop;
		m_accelCal.Y /= loop;
		m_accelCal.Z /= loop;
	}

	Mpu9250::Vec3 Mpu9250::rawGyro() noexcept {
		uint8_t buffer[6] = {0, 0, 0, 0, 0, 0};

		SPI::readRegs(0x43, buffer, 6);

		vec3Out.X = (buffer[0] << 8 | buffer[1]);
		vec3Out.Y = (buffer[2] << 8 | buffer[3]);
		vec3Out.Z = (buffer[4] << 8 | buffer[5]);

		// https://github.com/MarkSherstan/MPU-6050-9250-I2C-CompFilter/blob/master/Arduino/main/main.ino
		vec3Out.X = (double)vec3Out.X / 16.4;
		vec3Out.Y = (double)vec3Out.Y / 16.4;
		vec3Out.Z = (double)vec3Out.Z / 16.4;

		return vec3Out;
	}

	Mpu9250::Vec3 Mpu9250::rawAccel() noexcept {
		uint8_t buffer[6] = {0, 0, 0, 0, 0, 0};

		SPI::readRegs(0x3B, buffer, 6);

		vec3Out.X = (buffer[0] << 8 | buffer[1]);
		vec3Out.Y = (buffer[2] << 8 | buffer[3]);
		vec3Out.Z = (buffer[4] << 8 | buffer[5]);

		vec3Out.X = Misc::milli((double)vec3Out.X / 2048.0);
		vec3Out.Y = Misc::milli((double)vec3Out.Y / 2048.0);
		vec3Out.Z = Misc::milli((double)vec3Out.Z / 2048.0);

		return vec3Out;
	}

	Mpu9250::Vec3 Mpu9250::gyroVals() noexcept {
		auto raw = rawGyro();

		vec3Out.X = static_cast<int16_t>(Kalman::filter(gyroKalmanConfigs[0], raw.X - m_gyroCal.X));
		vec3Out.Y = static_cast<int16_t>(Kalman::filter(gyroKalmanConfigs[1], raw.Y - m_gyroCal.Y));
		vec3Out.Z = static_cast<int16_t>(Kalman::filter(gyroKalmanConfigs[2], raw.Z - m_gyroCal.Z));

		return vec3Out;
	}

	Mpu9250::Vec3 Mpu9250::filteredAccels() noexcept {
		auto rawAccels = rawAccel();

		auto accelX = static_cast<int16_t>(Kalman::filter(accelKalmanConfigs[0], rawAccels.X));
		auto accelY = static_cast<int16_t>(Kalman::filter(accelKalmanConfigs[1], rawAccels.Y));
		auto accelZ = static_cast<int16_t>(Kalman::filter(accelKalmanConfigs[2], rawAccels.Z));

		vec3Out = {accelX, accelY, accelZ};
		return vec3Out;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Static methods

	Mpu9250::Rotation Mpu9250::toAngles(const Vec3& acceleration) noexcept {
		Rotation out;

		float roll = std::atan2((float)acceleration.Y, (float)acceleration.Z) * (630.f / 11.f);
		float pitch = -(std::atan2((float)acceleration.X, (float)acceleration.Z) * (630.f / 11.f));

		out.roll = roll;
		out.pitch = pitch;

		return out;
	}

	void Mpu9250::debugPrint() noexcept {}
} // namespace PicoPilot