#include "pico/stdlib.h"
#include "hardware/i2c.h"

#include <iostream>
#include <array>
#include <stdlib.h>

#include "Helpers/Pico.hpp"
#include "Helpers/Misc.hpp"
#include "Helpers/Macros.hpp"
#include "PwmDevices/PwmDevices.hpp"
#include "Quad.hpp"
#include "Remote.hpp"

namespace Application {
	using namespace PicoPilot;
	
	// TODO: consider gpio 6,7,8,9
	Quad::Controls testQuad = Quad::Controls::create({10, 11, 12, 13});
	Remote remote0 = Remote::create();
	bool started = false;

	namespace Core0 {
		void setup() {
			while (remote0.getPacketData().rssi == 0) {
				std::cout << "waiting for signal...\n";
				sleep_ms(1000);
			}
			started = true;
		}
		void loop() {
			int16_t thrustData = remote0.getPacketData().data;
			testQuad.input(std::move(thrustData), (int16_t)511, (int16_t)511, (int16_t)511);
		}
	} // namespace Core0

	namespace Core1 {
		void setup() {
			Misc::Blink::setup();
		}
		void loop() {
			Misc::Blink::start();
			if (started) {
				testQuad.debugPrint();

				sleep_ms(100);
				printf("\033[2J");
			}
		}
	} // namespace Core1

} // namespace Application
