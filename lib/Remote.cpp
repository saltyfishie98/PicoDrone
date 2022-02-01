#include "Remote.hpp"

#include <stdio.h>

namespace PicoPilot {
	Remote Remote::create(long&& freq, uint&& ss, uint&& reset, uint&& dio0) {
		Remote temp;
		temp.setPins(ss, reset, dio0);
		if (!temp.begin(freq)) {
			printf("Failed\n");
			sleep_ms(500);
			abort();
		}

		return temp;
	}

	Remote::Packet Remote::getPacketData() {
		int packetSize = LoRaClass::parsePacket();

		if (packetSize) {
			std::string dataStr = "";

			while (LoRaClass::available()) {
				dataStr.push_back((char)LoRaClass::read());
			}

			if (dataStr.size() <= 4 && std::isdigit(dataStr.at(0))) {
				m_packetData.thrust = stoi(dataStr);
				m_packetData.rssi = LoRaClass::packetRssi();
				m_packetData.snr = LoRaClass::packetSnr();
			}
		}

		return m_packetData;
	}

	void Remote::waitForSignal() {
		while (getPacketData().rssi == 0) {
			printf("waiting for signal...\n");
			sleep_ms(1000);
		}
	}
} // namespace PicoPilot