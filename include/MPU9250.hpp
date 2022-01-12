#ifndef C__PROJECTS_PICO_PICODRONE_INCLUDE_MPU9250_HPP_
#define C__PROJECTS_PICO_PICODRONE_INCLUDE_MPU9250_HPP_

#include "pico/stdlib.h"
#include <array>

#include "Helpers/Pico.hpp"

namespace LocalLib {
	class mpu9250 {
	  public:
		struct Vec3 {
			int16_t X = 0;
			int16_t Y = 0;
			int16_t Z = 0;
		};

		struct Motion {
			int16_t roll = 0;
			int16_t pitch = 0;
			int16_t yaw = 0;
		};

		static mpu9250 create(uint&& miso = 4, uint&& cs = 5, uint&& sck = 6, uint&& mosi = 7);

		mpu9250() = default;

		void update();
		Vec3 rawAccel() noexcept;
		Vec3 rawGyro() noexcept;
		void calibrateGyro(uint8_t&& numLoop) noexcept;
		void reset() noexcept;

	  protected:
		mpu9250(uint&& miso, uint&& cs, uint&& sck, uint&& mosi);

	  private:
		Pico::SPI m_spi;
		Vec3 m_gyroCal;
	};
} // namespace LocalLib
#endif // C__PROJECTS_PICO_PICODRONE_INCLUDE_MPU9250_HPP_}