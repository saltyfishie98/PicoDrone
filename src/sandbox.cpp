#include "pico/stdlib.h"
#include "hardware/i2c.h"

#include <stdio.h>
#include <iostream>

#include "I2C/MPU6050.hpp"

#define I2C_PORT i2c0
const static uint8_t devAddr = 0x68;

bool mpu_init() {
	sleep_ms(1000);
	uint8_t reg = 0x75;
	uint8_t chipId[1];

	i2c_write_blocking(I2C_PORT, devAddr, &reg, 1, true);
	i2c_read_blocking(I2C_PORT, devAddr, chipId, 1, false);

	return chipId[0] == 0x68;
}

void wake() {
	uint8_t data_buf[2];
	uint8_t srcAddr = MPU6050_RA_PWR_MGMT_1;

	i2c_write_blocking(I2C_PORT, devAddr, &srcAddr, 1, true);
	i2c_read_blocking(I2C_PORT, devAddr, data_buf, 1, false);
}

void get_data() {
	uint8_t data_buf[2];
	uint8_t srcAddr = MPU6050_RA_ACCEL_XOUT_H;

	i2c_write_blocking(I2C_PORT, devAddr, &srcAddr, 1, true);
	i2c_read_blocking(I2C_PORT, devAddr, data_buf, 2, false);

	uint16_t data = (data_buf[0] << 8) | data_buf[1];

	printf("Accel - X: %d\n", data);
}

void sandbox() {
	i2c_init(I2C_PORT, 400000);

	gpio_set_function(21, GPIO_FUNC_I2C);
	gpio_set_function(20, GPIO_FUNC_I2C);
	gpio_pull_up(21);
	gpio_pull_up(20);

	if (mpu_init()) {
		while (1) {
			get_data();
		}

	} else {
		puts("Error!\n");
	}

	while (1) {}
}