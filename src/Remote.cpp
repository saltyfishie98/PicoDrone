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

		temp.setSpreadingFactor(7);
		temp.setCodingRate4(5);
		temp.setSignalBandwidth(250E3);

		return temp;
	}

	Remote::Packet Remote::getPacketData() noexcept {
		int packetSize = LoRaClass::parsePacket();

		if (packetSize) {
			uint8_t msgBuff[8];
			static uint64_t dataBuffer = 0;

			memset(msgBuff, 0, sizeof(msgBuff));
			uint8_t cntr = 0;
			while (LoRaClass::available() > 0) {
				if (cntr < (sizeof(msgBuff) / sizeof(msgBuff[0]))) {
					msgBuff[cntr] = LoRaClass::read();
					cntr++;
				} else // discard any extra data
					LoRa.read();
			}

			memmove(&dataBuffer, msgBuff, sizeof(msgBuff));

			m_packetData.thrust = (dataBuffer >> 0) & 0b1111111111111111;
			m_packetData.yaw = (dataBuffer >> 16) & 0b1111111111111111;
			m_packetData.pitch = (dataBuffer >> 32) & 0b1111111111111111;
			m_packetData.roll = (dataBuffer >> 48) & 0b1111111111111111;
			m_packetData.rssi = LoRaClass::packetRssi();
			m_packetData.snr = LoRaClass::packetSnr();
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
			printf("thrust: %d\nyaw   : %d\npitch : %d\nroll  : %d\n\n", data.thrust, data.yaw, data.pitch, data.roll);
		})
	}
} // namespace PicoPilot