#ifndef C__PROJECTS_PICO_PICODRONE_INCLUDE_MPU9250_HPP_
#define C__PROJECTS_PICO_PICODRONE_INCLUDE_MPU9250_HPP_

#include "Helpers/Pico.hpp"
#include "pico/time.h"

namespace PicoPilot {
	class Mpu9250 : public Pico::SPI {
	  public:
		static Mpu9250 create(spi_inst_t* port, SPI::Pins&& gpioPins, uint CalibrationLoop) noexcept;

		Mpu9250() = default;

		struct Vec3 {
			int16_t X = 0;
			int16_t Y = 0;
			int16_t Z = 0;
		};

		struct Rotation {
			int16_t pitch = 0;
			int16_t roll = 0;
			int16_t yaw = 0;
		};

		void reset() noexcept;
		void calibrate(uint loop = 100) noexcept;
		void debugPrint() noexcept;
		Vec3 rawAccel() noexcept;
		Vec3 rawGyro() noexcept;
		Vec3 calibratedGyro() noexcept;
		Rotation anglesFromAccel() noexcept;
		Rotation filteredAngles(double&& pitchTau = 0.75, double&& rollTau = 0.75) noexcept;

	  protected:
		Mpu9250(spi_inst_t* port, SPI::Pins&& gpioPins);
		void begin() noexcept;

	  private:
		Vec3 m_gyroCal;
		Vec3 m_accel;
		Rotation m_filteredAngles;
		absolute_time_t m_compLastTime = get_absolute_time();
		Vec3 vec3Out;
		Rotation rotationOut;

		void m_updateGyroAngles();
	};
} // namespace PicoPilot

#endif // C__PROJECTS_PICO_PICODRONE_INCLUDE_MPU9250_HPP_