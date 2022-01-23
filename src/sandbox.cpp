#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/clocks.h"

#include "CpMpu9250.hpp"
#include "MPU9250.hpp"
#include "Helpers/Pico.hpp"
#include "Helpers/Misc.hpp"

mpu9250 mpu(100); // Creates an mpu object

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
	Misc::Blink::setup();

	while (1) {
		Misc::Blink::start();

		auto euler = test.anglesFromAccel();
		auto raw = test.rawGyro();
		auto calGyro = test.calibratedGyro();
		auto filtered = test.filteredAngles(0.75, 0.75);

		printf("Cpu Clock: %lu\n", clock_get_hz(clk_sys));
		printf("Raw Gyro. X = %d, Y = %d, Z = %d\n", raw.X, raw.Y, raw.Z);
		printf("calibrated Gyro. X = %d, Y = %d, Z = %d\n", calGyro.X, calGyro.Y, calGyro.Z);
		printf("Accel Angles     - Pitch: %d, Roll: %d \n", euler.pitch, euler.roll);
		printf("filtered Angles  - Pitch: %d, Roll: %d \n", filtered.pitch, filtered.roll);

		sleep_ms(60);

		printf("\033[2J");
	}
}