#include "Remote.hpp"

#include <stdio.h>

namespace LocalLib {
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

			m_packetData.data = stoi(dataStr);
			m_packetData.rssi = LoRaClass::packetRssi();
			m_packetData.snr = LoRaClass::packetSnr();
		}

		return m_packetData;
	}
} // namespace LocalLib