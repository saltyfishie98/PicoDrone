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
			std::string dataStr;

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