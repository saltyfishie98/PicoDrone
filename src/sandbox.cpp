#include <iostream>
#include <stdio.h>

#include "LoRa-RP2040.h"

void sandbox() {
	LoRa.setPins(17, 27, 26);

	if (!LoRa.begin(433E6)) {
		printf("Failed\n");
		sleep_ms(500);
		abort();
	}

	printf("Success!\n");

	while (1) {
		int packetSize = LoRa.parsePacket();
		if (packetSize) {
			std::string dataStr = "";
			while (LoRa.available()) {
				dataStr.push_back((char)LoRa.read());
			}

			int data = std::stoi(dataStr);

			printf("%d", data);

			// print RSSI of packet
			printf("\nRSSI: ");
			printf("%d\n", LoRa.packetRssi());
		}
	}
}
