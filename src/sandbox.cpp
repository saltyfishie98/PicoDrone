#include <iostream>
#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"

#include "hardware/i2c.h"
#include "MPU9250.hpp"

void sandbox() {
	using namespace LocalLib;

	mpu9250 mpu = mpu9250::create();

	while (1) {
		auto accel = mpu.rawAccel();
		auto gyro = mpu.rawGyro();

		printf("accel: X: %d, Y:%d, Z:%d \n", accel.X, accel.Y, accel.Z);
		printf("gyro: X: %d, Y:%d, Z:%d \n\n", gyro.X, gyro.Y, gyro.Z);

		sleep_ms(100);
		printf("\033[2J");
	}
}
