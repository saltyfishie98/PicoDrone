#ifndef C__PROJECTS_PICO_PICODRONE_INCLUDE_REMOTE_HPP_
#define C__PROJECTS_PICO_PICODRONE_INCLUDE_REMOTE_HPP_

#include "pico/stdlib.h"
#include <string>

#include "../vendor/pico-lora/src/LoRa-RP2040.h"

namespace PicoPilot {
	class Remote : public LoRaClass {
	  public:
		Remote() = default;

		struct Packet {
			uint16_t thrust = 0;
			uint16_t yaw = 511;
			uint16_t pitch = 511;
			uint16_t roll = 511;
			int rssi = 0;
			float snr = 0;
		};

		static Remote create(long&& freq = 433E6, uint&& ss = 17, uint&& reset = 27, uint&& Dio0 = 26) noexcept;
		Packet getPacketData() noexcept;
		void waitForSignal() noexcept;
		void debugPrint() noexcept;

	  protected:
		Remote(long&& freq, uint&& ss, uint&& reset, uint&& Dio0);

	  private:
		Packet m_packetData;
	};
} // namespace PicoPilot

#endif // C__PROJECTS_PICO_PICODRONE_INCLUDE_REMOTE_HPP_