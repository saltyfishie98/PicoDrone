#include <stdio.h>
#include "pico/stdlib.h"

#include "CpMpu9250.hpp"
#include "MPU9250.hpp"
#include "Helpers/Pico.hpp"

// mpu9250 mpu(100); // Creates an mpu object

// void sandbox() {
// 	printf("Hello, MPU9250! Reading raw data from registers via SPI...\n");

// 	while (1) {
// 		mpu.updateAngles(); // Uses the object to calculate the angles
// 		mpu.printData();	// Uses the object to print the data
// 	}
// }

void sandbox() {
	using namespace PicoPilot;

	Pico::SPI::Pins pins;
	Mpu9250 test = Mpu9250::create(spi1, std::move(pins), 100);

	while (1) {
		auto euler = test.eulerAngles();
		auto abs = test.AbsAngles();
		auto raw = test.rawGyro();
		auto calGyro = test.calibratedGyro();

		printf("Raw Gyro. X = %d, Y = %d, Z = %d\n", raw.X, raw.Y, raw.Z);
		printf("calibrated Gyro. X = %d, Y = %d, Z = %d\n", calGyro.X, calGyro.Y, calGyro.Z);
		printf("Euler - Pitch: %d, Roll: %d \n", euler.pitch, euler.roll);
		printf("Abs   - Pitch: %d, Roll: %d \n", abs.pitch, abs.roll);

		sleep_ms(100);

		printf("\033[2J");
	}
}