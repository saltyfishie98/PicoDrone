#include "pico/stdlib.h"
#include "hardware/uart.h"
#include <iostream>
#include <stdio.h>

#include "Quad.hpp"

void sandbox() {
	using namespace LocalLib;

	uart_init(uart1, 19200);
	gpio_set_function(9, GPIO_FUNC_UART);
	uart_set_fifo_enabled(uart1, true);

	uint16_t data = 0;
	uint16_t thrust = 0;
	uint16_t yaw = 0;
	uint16_t pitch = 0;
	uint16_t roll = 0;

	Quad::Controls test = Quad::Controls::create({4, 5, 6, 7});

	while (true) {
		uart_read_blocking(uart1, (uint8_t*)&data, 2);
		if (data == 0xFFFF) {
			uart_read_blocking(uart1, (uint8_t*)&thrust, 2);
			uart_read_blocking(uart1, (uint8_t*)&yaw, 2);
			uart_read_blocking(uart1, (uint8_t*)&pitch, 2);
			uart_read_blocking(uart1, (uint8_t*)&roll, 2);
		}

		test.input(thrust, yaw, pitch, roll);

		printf("thrust: %u\n", thrust);
		printf("yaw: %u\n", yaw);
		printf("pitch: %u\n", pitch);
		printf("roll: %u\n\n", roll);
	}
}