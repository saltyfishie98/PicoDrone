#include "pico/stdlib.h"
#include "hardware/i2c.h"

#include <iostream>
#include <stdlib.h>

#include "Helpers/Pico.hpp"
#include "Helpers/Misc.hpp"
#include "I2C/Comms.hpp"
#include "I2C/MPU6050.hpp"
#include "Quad.hpp"

namespace Application {
	using namespace LocalLib::Helpers;
	using namespace LocalLib;

	const uint led = PICO_DEFAULT_LED_PIN;
	bool toggle = 0;
	void setupBlink() {
		gpio_init(led);
		gpio_set_dir(led, true);
	}
	void blink() {
		if (Misc::interval(250)) {
			toggle ^= 1UL << 0;
			gpio_put(led, toggle);
		}
	}

	namespace Core0 {
		Pico::AnalogReader pot0 = Pico::AnalogReader::create(27);
		Quad::SpeedControls quad0 = Quad::SpeedControls::create({4, 5, 6, 7});
		Quad::MotorSpeedCfg speedConfig = CLEAN_SPD_CONFIG;

		void setup() {}
		void loop() {
			Quad::configureMotorSpeed(&speedConfig, Quad::Motor::_0, pot0.read());
			Quad::configureMotorSpeed(&speedConfig, Quad::Motor::_1, pot0.read());
			Quad::configureMotorSpeed(&speedConfig, Quad::Motor::_2, pot0.read());
			Quad::configureMotorSpeed(&speedConfig, Quad::Motor::_3, pot0.read());

			quad0.uploadSpeedCfg(speedConfig);
		}
	} // namespace Core0

	namespace Core1 {
		// I2C::Comms mpu6050 = I2C::Comms::create(0x68, i2c0, 21, 20, 400000);

		uint16_t data = 0;
		uint8_t dataBuf[2];

		void setup() {
			// setupBlink();
			// mpu6050.writeBit(MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_SLEEP_BIT, 0);
		}
		void loop() {
			// blink();

			// if (mpu6050.connected()) {
			// 	mpu6050.readBytes(MPU6050_RA_ACCEL_ZOUT_H, 2, dataBuf);
			// 	data = (dataBuf[0] << 8) | dataBuf[1];
			// 	// printf("Accel Z: %d\n", data);

			// } else {
			// 	puts("Error!\n");
			// }
		}
	} // namespace Core1

} // namespace Application
