#include "MPU9250.hpp"

#include <stdio.h>
#include <math.h>

using namespace Pico;

namespace PicoPilot {
	Mpu9250::Rotation anglesFromAccel(Mpu9250::Vec3 accel) {

		float accTotalVector = sqrt((accel.X * accel.X) + (accel.Y * accel.Y) + (accel.Z * accel.Z));

		float anglePitchAcc = asin(accel.Y / accTotalVector) * 57.296;
		float angleRollAcc = asin(accel.X / accTotalVector) * -57.296;

		Mpu9250::Rotation angle;
		angle.pitch = anglePitchAcc;
		angle.roll = angleRollAcc;

		return angle;
	}

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

	void Mpu9250::begin() {
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
		m_usSinceLastReading = get_absolute_time();
	}

	void Mpu9250::reset() {
		uint8_t buf[] = {0x6B, 0x00};
		SPI::write_registers(buf, 2);
	}

	Mpu9250::Vec3 Mpu9250::rawGyro() {
		uint8_t buffer[6] = {0, 0, 0, 0, 0, 0};
		Mpu9250::Vec3 data;

		SPI::read_registers(0x43, buffer, 6);

		data.X = (buffer[0] << 8 | buffer[1]);
		data.Y = (buffer[2] << 8 | buffer[3]);
		data.Z = (buffer[4] << 8 | buffer[5]);

		return data;
	}

	Mpu9250::Vec3 Mpu9250::calibratedGyro() {
		auto raw = rawGyro();
		Mpu9250::Vec3 out;

		out.X = raw.X - m_gyroCal.X;
		out.Y = raw.Y - m_gyroCal.Y;
		out.Z = raw.Z - m_gyroCal.Z;

		return out;
	}

	Mpu9250::Vec3 Mpu9250::rawAccel() {
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

	Mpu9250::Rotation Mpu9250::AbsAngles() {
		auto tempEulerAngles = eulerAngles();
		Mpu9250::Rotation fullAngles;

		if (m_accel.Y > 0 && m_accel.Z > 0)
			fullAngles.roll = tempEulerAngles.roll;
		if (m_accel.Y > 0 && m_accel.Z < 0)
			fullAngles.roll = 180 - tempEulerAngles.roll;
		if (m_accel.Y < 0 && m_accel.Z < 0)
			fullAngles.roll = 180 - tempEulerAngles.roll;
		if (m_accel.Y < 0 && m_accel.Z > 0)
			fullAngles.roll = 360 + tempEulerAngles.roll;

		if (m_accel.X < 0 && m_accel.Z > 0)
			fullAngles.pitch = tempEulerAngles.pitch;
		if (m_accel.X < 0 && m_accel.Z < 0)
			fullAngles.pitch = 180 - tempEulerAngles.pitch;
		if (m_accel.X > 0 && m_accel.Z < 0)
			fullAngles.pitch = 180 - tempEulerAngles.pitch;
		if (m_accel.X > 0 && m_accel.Z > 0)
			fullAngles.pitch = 360 + tempEulerAngles.pitch;

		return fullAngles;
	}

	Mpu9250::Rotation Mpu9250::eulerAngles() {
		m_accel = rawAccel();
		auto gyro = Mpu9250::calibratedGyro();
		Mpu9250::Rotation eulerAngles;

		long hertz = 1000000 / absolute_time_diff_us(m_usSinceLastReading, get_absolute_time());

		if (hertz < 200) {
			return anglesFromAccel(m_accel);
		}

		long temp = 1.l / (hertz * 65.5l);

		eulerAngles.roll += gyro.X * temp;
		eulerAngles.pitch += gyro.Y * temp;

		eulerAngles.roll += eulerAngles.pitch * sin(gyro.Z * temp * 0.1f);
		eulerAngles.pitch -= eulerAngles.roll * sin(gyro.Z * temp * 0.1f);

		auto accelEuler = anglesFromAccel(m_accel);

		eulerAngles.roll = eulerAngles.roll * 0.9996 + accelEuler.pitch * 0.0004;
		eulerAngles.pitch = eulerAngles.pitch * 0.9996 + accelEuler.roll * 0.0004;

		return eulerAngles;
	}

} // namespace PicoPilot