#include "Remote.hpp"

#include <stdio.h>
#include "Helpers/Macros.hpp"

namespace PicoPilot {
	Remote Remote::create(long&& freq, uint&& ss, uint&& reset, uint&& dio0) noexcept {
		Remote temp;
		temp.setPins(ss, reset, dio0);
		if (!temp.begin(freq)) {
			DEBUG_RUN({
				printf("Failed\n");
				sleep_ms(500);
				abort();
			})
		}

		return temp;
	}

	Remote::Packet Remote::getPacketData() noexcept {
		int packetSize = LoRaClass::parsePacket();

		if (packetSize) {
			char dataStr[6] = "";

			uint8_t i = 0;
			while (LoRaClass::available()) {
				dataStr[i] = (char)LoRaClass::read();
				if (i > 6) {
					return m_packetData;
				}
				++i;
			}

			if (strlen(dataStr) <= 4 && std::isdigit(dataStr[0])) {
				m_packetData.thrust = strtol(dataStr, nullptr, 10);
				m_packetData.rssi = LoRaClass::packetRssi();
				m_packetData.snr = LoRaClass::packetSnr();
			}
		}

		return m_packetData;
	}

	void Remote::waitForSignal() noexcept {
		while (getPacketData().rssi == 0) {
			DEBUG_RUN(printf("waiting for signal...\n");)
			sleep_ms(1000);
		}
	}

	void Remote::debugPrint() noexcept {
		DEBUG_RUN({
			auto data = getPacketData();
			printf("thrust: %d\nyaw   : %d\npitch : %d\nroll  : %d\n", data.thrust, data.yaw, data.pitch, data.roll);
		})
	}
} // namespace PicoPilot