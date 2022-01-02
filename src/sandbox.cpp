#include <iostream>
#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"

#include "hardware/i2c.h"
#include "MPU9250.hpp"

void sandbox() {
	mpu9250 mpu(100);
	sleep_ms(10000);

	printf("Hello, MPU9250! Reading raw data from registers via SPI...\n");

	while (1) {
		mpu.updateAngles(); // Uses the object to calculate the angles
		mpu.printData();	// Uses the object to print the data
	}
}

// bool reserved_addr(uint8_t addr) {
// 	return (addr & 0x78) == 0 || (addr & 0x78) == 0x78;
// }
// void sandbox() {
// 	// This example will use I2C0 on the default SDA and SCL pins (4, 5 on a Pico)
// 	i2c_init(i2c0, 100 * 1000);
// 	gpio_set_function(20, GPIO_FUNC_I2C);
// 	gpio_set_function(21, GPIO_FUNC_I2C);
// 	gpio_pull_up(20);
// 	gpio_pull_up(21);
// 	// Make the I2C pins available to picotool
// 	bi_decl(bi_2pins_with_func(20, 21, GPIO_FUNC_I2C));

// 	printf("\nI2C Bus Scan\n");
// 	printf(" 0 1 2 3 4 5 6 7 8 9 A B C D E F\n");

// 	for (int addr = 0; addr < (1 << 7); ++addr) {
// 		if (addr % 16 == 0) {
// 			printf("%02x ", addr);
// 		}
// 		// Perform a 1-byte dummy read from the probe address. If a slave
// 		// acknowledges this address, the function returns the number of bytes
// 		// transferred. If the address byte is ignored, the function returns
// 		// -1.
// 		// Skip over any reserved addresses.
// 		int ret;
// 		uint8_t rxdata;
// 		if (reserved_addr(addr))
// 			ret = PICO_ERROR_GENERIC;
// 		else
// 			ret = i2c_read_blocking(i2c_default, addr, &rxdata, 1, false);
// 		printf(ret < 0 ? "." : "@");
// 		printf(addr % 16 == 15 ? "\n" : " ");
// 	}
// 	printf("Done.\n");
// }
