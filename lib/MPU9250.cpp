#include "MPU9250.hpp"

#include <stdio.h>
#include <cmath>
#include "hardware/clocks.h"
#include "Helpers/Macros.hpp"
#include "Helpers/Misc.hpp"

using namespace Pico;

namespace PicoPilot {
	Mpu9250::Mpu9250(spi_inst_t* port, SPI::Pins&& gpioPins) {
		SPI::m_port = port;
		SPI::m_pins = std::move(gpioPins);
	}

	Mpu9250 Mpu9250::create(spi_inst_t* port, SPI::Pins&& gpioPins, uint calibrationLoop) {
		Mpu9250 temp(port, std::move(gpioPins));
		temp.begin();
		temp.calibrate(calibrationLoop);
		return temp;
	}

	void Mpu9250::begin() noexcept {
		SPI::begin();
		reset();

		uint8_t data = 0;
		SPI::read_registers(0x75, &data, 1);
		sleep_ms(10);

		if (data != 0x71) {
			DEBUG_RUN(printf("Mpu9250 begin error!\n");)
			while (1) {}
		}

		// Read and set DLPF_CFG
		SPI::read_registers(0x1A, &data, 1);
		data |= 4 << 0;
		uint8_t dlpfCfgBuf[] = {0x1A, data};
		SPI::write_registers(dlpfCfgBuf, 2);

		// Read and set FCHOICE_B to use DLPF_CFG
		SPI::read_registers(0x1B, &data, 1);
		data |= 0b00 << 0;
		uint8_t fchoicebBuf[] = {0x1B, data};
		SPI::write_registers(fchoicebBuf, 2);

		// Read and set A_DLPF_CFG and ACCEL_FCHOICE to use A_DLPF_CFG
		SPI::read_registers(0x1C, &data, 1);
		data |= 4 << 0;
		data |= 0 << 3;
		uint8_t accelDlpfCfgBuf[] = {0x1C, data};
		SPI::write_registers(accelDlpfCfgBuf, 2);

		calibrate();
	}

	void Mpu9250::reset() noexcept {
		// uint8_t data = 0;
		// read_registers(0x6B, &data, 1);
		// data |= 1 << 7;
		// uint8_t hResetBuf[] = {0x6B, data};
		// SPI::write_registers(hResetBuf, 2);

		uint8_t buf[] = {0x6B, 0x00};
		SPI::write_registers(buf, 2);
	}

	Mpu9250::Vec3 Mpu9250::rawGyro() noexcept {
		uint8_t buffer[6] = {0, 0, 0, 0, 0, 0};

		SPI::read_registers(0x43, buffer, 6);

		vec3Out.X = (buffer[0] << 8 | buffer[1]);
		vec3Out.Y = (buffer[2] << 8 | buffer[3]);
		vec3Out.Z = (buffer[4] << 8 | buffer[5]);

		// https://github.com/MarkSherstan/MPU-6050-9250-I2C-CompFilter/blob/master/Arduino/main/main.ino
		vec3Out.X = (double)vec3Out.X / 131.0;
		vec3Out.Y = (double)vec3Out.Y / 131.0;
		vec3Out.Z = (double)vec3Out.Z / 131.0;

		return vec3Out;
	}

	Mpu9250::Vec3 Mpu9250::calibratedGyro() noexcept {
		auto raw = rawGyro();

		vec3Out.X = raw.X - m_gyroCal.X;
		vec3Out.Y = raw.Y - m_gyroCal.Y;
		vec3Out.Z = raw.Z - m_gyroCal.Z;

		return vec3Out;
	}

	Mpu9250::Vec3 Mpu9250::rawAccel() noexcept {
		uint8_t buffer[6] = {0, 0, 0, 0, 0, 0};

		SPI::read_registers(0x3B, buffer, 6);

		vec3Out.X = (buffer[0] << 8 | buffer[1]);
		vec3Out.Y = (buffer[2] << 8 | buffer[3]);
		vec3Out.Z = (buffer[4] << 8 | buffer[5]);

		vec3Out.X = Misc::milli((double)vec3Out.X / 16384.0);
		vec3Out.Y = Misc::milli((double)vec3Out.Y / 16384.0);
		vec3Out.Z = Misc::milli((double)vec3Out.Z / 16384.0);

		return vec3Out;
	}

	void Mpu9250::calibrate(uint loop) {
		Mpu9250::Vec3 tempGyro;
		Mpu9250::Vec3 tempAccel;

		for (int i = 0; i < loop; i++) {
			tempGyro = rawGyro();
			tempAccel = rawAccel();

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

	Mpu9250::Rotation Mpu9250::anglesFromAccel() noexcept {
		Vec3 accel = rawAccel();

		float roll = std::atan2((float)accel.Y, (float)accel.Z) * (630.f / 11.f);
		float pitch = -(std::atan2((float)accel.X, (float)accel.Z) * (630.f / 11.f));

		rotationOut.roll = roll;
		rotationOut.pitch = pitch;

		return rotationOut;
	}

	Mpu9250::Rotation Mpu9250::filteredAngles(double&& pitchTau, double&& rollTau) noexcept {
		auto gyroRate = calibratedGyro();
		auto accelAngles = anglesFromAccel();

		double deltaT = (double)absolute_time_diff_us(m_compLastTime, get_absolute_time()) / 1000000.0;
		m_compLastTime = get_absolute_time();

		double rollRate = gyroRate.X;
		double pitchRate = gyroRate.Y;

		double accelRoll = accelAngles.roll;
		double accelPitch = accelAngles.pitch;

		m_filteredAngles.roll = rollTau * (m_filteredAngles.roll + rollRate * deltaT) + (1 - rollTau) * accelRoll;
		m_filteredAngles.pitch = pitchTau * (m_filteredAngles.pitch + pitchRate * deltaT) + (1 - pitchTau) * accelPitch;

		return m_filteredAngles;
	}

	void Mpu9250::debugPrint() noexcept {
		// DEBUG_RUN({
		auto gyroRaw = rawGyro();
		auto accelRaw = rawAccel();

		auto calGyro = calibratedGyro();
		auto accelAngles = anglesFromAccel();
		auto angleFiltered = filteredAngles(0.8, 0.8);

		uint8_t data = 0;
		SPI::read_registers(0x1A, &data, 1);
		printf("DLPF_CFG = %d\n", data & 0b111);

		SPI::read_registers(0x1B, &data, 1);
		printf("FCHOICE_B = %d\n\n", data & 0b11);

		printf("Raw Acc. X = %d, Y = %d, Z = %d\n", accelRaw.X, accelRaw.Y, accelRaw.Z);
		printf("Raw Gyro. X = %d, Y = %d, Z = %d\n", gyroRaw.X, gyroRaw.Y, gyroRaw.Z);
		printf("calibrated Gyro. X = %d, Y = %d, Z = %d\n\n", calGyro.X, calGyro.Y, calGyro.Z);

		printf("Angles from Accel. Pitch = %d, roll = %d\n", accelAngles.pitch, accelAngles.roll);
		printf("filtered angles.   Pitch = %d, roll = %d\n", angleFiltered.pitch, angleFiltered.roll);
		// })
	}
} // namespace PicoPilot