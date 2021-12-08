#include "pico/stdlib.h"
#include "hardware/i2c.h"

#include <stdio.h>
#include <iostream>

#include "I2C/MPU6050.hpp"
#include "I2C/I2CComms.hpp"

#define I2C_PORT i2c0
const static uint8_t devAddr = 0x68;

using namespace LocalLib;

void sandbox() {
	I2CComms mpu6050 = I2CComms::create(devAddr, I2C_PORT, 21, 20, 400000);
	uint16_t data = 0;

	if (mpu6050.connected()) {
		uint8_t data_buf[2];

		mpu6050.writeBit(MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_SLEEP_BIT, 0);

		while (1) {
			mpu6050.readBytes(MPU6050_RA_ACCEL_ZOUT_H, 2, data_buf);

			data = (data_buf[0] << 8) | data_buf[1];

			printf("Accel Z: %d\n", data);
		}

	} else {
		puts("Error!\n");
	}

	while (1) {}
}