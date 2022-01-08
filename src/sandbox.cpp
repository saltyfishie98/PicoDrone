#include <iostream>
#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"

#include "hardware/i2c.h"
#include "MPU9250.hpp"

void sandbox() {
	using namespace LocalLib;

	mpu9250 mpu = mpu9250::create();
	sleep_ms(10000);

	while (1) {}
}
