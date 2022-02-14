#ifndef C__PROJECTS_PICO_PICODRONE_INCLUDE_MPU9250_HPP_
#define C__PROJECTS_PICO_PICODRONE_INCLUDE_MPU9250_HPP_

#include "Helpers/Pico.hpp"
#include "Helpers/Misc.hpp"
#include "pico/time.h"

namespace PicoPilot {
	class Mpu9250 : public Pico::SPI {
	  public:
		template <typename T>
		struct Vec3 {
			T X = 0;
			T Y = 0;
			T Z = 0;
		};

		template <typename T>
		struct Rotation {
			T pitch = 0;
			T roll = 0;
			T yaw = 0;
		};

		using QuadVec3 = Vec3<int16_t>;
		using QuadRotation = Vec3<int16_t>;

		static Mpu9250 create(spi_inst_t* port, SPI::Pins&& gpioPins) noexcept;
		QuadVec3 gyroVals();
		QuadVec3 accelMilliVals();
		void checkSettings();
		void checkMpuVals();

	  protected:
		Mpu9250(spi_inst_t* port, SPI::Pins&& gpioPins);
		void begin() noexcept;
		void reset() noexcept;

	  private:
		Vec3<float> m_accelOffset;
		Vec3<float> m_gyroOffset;
		QuadVec3 m_prevGyro;
		QuadVec3 m_prevAccel;
		uint8_t data = 0;

		void getMpuOffsets();
		QuadVec3 getRawMilliAccel();
		QuadVec3 getRawGyro();
		void setGyroSens();
		void setAccelSens();
	};
} // namespace PicoPilot

#endif // C__PROJECTS_PICO_PICODRONE_INCLUDE_MPU9250_HPP_