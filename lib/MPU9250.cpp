#include "MPU9250.hpp"

#include <stdio.h>
#include <cmath>

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

		uint8_t id = 0;
		SPI::read_registers(0x75, &id, 1);
		sleep_ms(10);

		if (id != 0x71) {
			printf("Mpu9250 begin error!\n");
			while (1) {}
		}

		calibrate();
	}

	void Mpu9250::reset() noexcept {
		uint8_t buf[] = {0x6B, 0x00};
		SPI::write_registers(buf, 2);
	}

	Mpu9250::Vec3 Mpu9250::rawGyro() noexcept {
		uint8_t buffer[6] = {0, 0, 0, 0, 0, 0};
		Mpu9250::Vec3 data;

		SPI::read_registers(0x43, buffer, 6);

		data.X = (buffer[0] << 8 | buffer[1]);
		data.Y = (buffer[2] << 8 | buffer[3]);
		data.Z = (buffer[4] << 8 | buffer[5]);

		return data;
	}

	Mpu9250::Vec3 Mpu9250::calibratedGyro() noexcept {
		auto raw = rawGyro();
		Mpu9250::Vec3 out;

		// https://github.com/MarkSherstan/MPU-6050-9250-I2C-CompFilter/blob/master/Arduino/main/main.ino
		out.X = (double)(raw.X - m_gyroCal.X) / 131.0;
		out.Y = (double)(raw.Y - m_gyroCal.Y) / 131.0;
		out.Z = (double)(raw.Z - m_gyroCal.Z) / 131.0;

		return out;
	}

	Mpu9250::Vec3 Mpu9250::rawAccel() noexcept {
		uint8_t buffer[6] = {0, 0, 0, 0, 0, 0};
		Mpu9250::Vec3 data;

		SPI::read_registers(0x3B, buffer, 6);

		data.X = (buffer[0] << 8 | buffer[1]);
		data.Y = (buffer[2] << 8 | buffer[3]);
		data.Z = (buffer[4] << 8 | buffer[5]);

		return data;
	}

	void Mpu9250::calibrate(uint loop) {
		Mpu9250::Vec3 temp;
		for (int i = 0; i < loop; i++) {
			temp = rawGyro();
			m_gyroCal.X += temp.X;
			m_gyroCal.Y += temp.Y;
			m_gyroCal.Z += temp.Z;
		}
		m_gyroCal.X /= loop;
		m_gyroCal.Y /= loop;
		m_gyroCal.Z /= loop;
	}

	Mpu9250::Rotation Mpu9250::anglesFromAccel() noexcept {
		Rotation out;
		Vec3 accel = rawAccel();

		float roll = std::atan2((float)accel.Y, (float)accel.Z) * (630.f / 11.f);
		float pitch = -(std::atan2((float)accel.X, (float)accel.Z) * (630.f / 11.f));

		out.roll = roll;
		out.pitch = pitch;

		return out;
	}

	Mpu9250::Rotation Mpu9250::filteredAngles(double&& pitchTau, double&& rollTau) noexcept {
		// FilteredAngle = 0.98 * (FilteredAngle + d°/ s * time_between_cycles) + 0.02 * AccelerometerAngle;

		auto gyroRate = calibratedGyro();
		auto accelAngles = anglesFromAccel();
		double deltaT = (double)absolute_time_diff_us(m_compLastTime, get_absolute_time()) / 1000000.0;
		m_compLastTime = get_absolute_time();

		double rollRate = gyroRate.X;
		double pitchRate = gyroRate.Y;

		double accelRoll = accelAngles.roll;
		double accelPitch = accelAngles.pitch;

		m_filteredAngles.roll = rollTau * (m_filteredAngles.roll + rollRate * deltaT) + (1 - rollTau) * accelRoll;
		m_filteredAngles.pitch = pitchTau * (m_filteredAngles.pitch + pitchRate * deltaT) - (1 - pitchTau) * accelPitch;

		return m_filteredAngles;
	}

} // namespace PicoPilot