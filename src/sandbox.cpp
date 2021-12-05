#include "pico/stdlib.h"
#include "hardware/i2c.h"

#include <stdio.h>
#include <iostream>

#define I2C_PORT i2c0

static int addr = 0x68;

void mpu_init() {
	sleep_ms(1000);
	uint8_t reg = 0x75;
	uint8_t chipId[1];

	i2c_write_blocking(I2C_PORT, addr, &reg, 1, true);
	i2c_read_blocking(I2C_PORT, addr, chipId, 1, false);

	printf("Chip ID: %x\n", chipId[0]);
}

void sandbox() {
	i2c_init(I2C_PORT, 400000);

	gpio_set_function(21, GPIO_FUNC_I2C);
	gpio_set_function(20, GPIO_FUNC_I2C);
	gpio_pull_up(21);
	gpio_pull_up(20);

	mpu_init();

	while (1) {}
}