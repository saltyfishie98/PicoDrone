#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "hardware/clocks.h"

#include <array>
#include <stdlib.h>

#include "FastPID.h"

#include "Helpers/Pico.hpp"
#include "Helpers/Misc.hpp"
#include "Helpers/Macros.hpp"
#include "PwmDevices/MotorESC.hpp"
#include "Quad.hpp"
#include "Remote.hpp"
#include "MPU9250.hpp"

namespace Application {
	using namespace PicoPilot;

	namespace Core0 {
		auto defaultPins = Mpu9250::Pins();
		auto mpu9250 = Mpu9250::create(spi1, std::move(defaultPins), 100);

		void setup() {}
		void loop() {
			mpu9250.debugPrint();
			sleep_ms(50);
			Misc::clearConsole();
		}
	} // namespace Core0

	namespace Core1 {

		void setup() {
			Misc::Blink::setup();
		}
		void loop() {
			Misc::Blink::start(250);
		}
	} // namespace Core1

} // namespace Application
