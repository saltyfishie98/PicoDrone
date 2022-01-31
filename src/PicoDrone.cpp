#include "pico/stdlib.h"
#include "hardware/i2c.h"

#include <array>
#include <stdlib.h>

#include "Helpers/Pico.hpp"
#include "Helpers/Misc.hpp"
#include "Helpers/Macros.hpp"

#include "PwmDevices/MotorESC.hpp"
#include "Quad.hpp"
#include "Remote.hpp"
#include "MPU9250.hpp"
#include "Pid.hpp"

namespace Application {
	using namespace PicoPilot;

	int16_t centerOffset = 511;

	bool started = false;
	auto defaultPins = Pico::SPI::Pins();
	auto defaultConfigs = Pid::Configs();

	auto controllerData = Remote::Packet();
	auto quadControls = Quad::Controls::create({6, 7, 8, 9});
	auto remote = Remote::create();
	auto mpu9250 = Mpu9250::create(spi1, std::move(defaultPins), 100);

	namespace Core0 {
		auto pitchPid = Pid::create(defaultConfigs);
		auto rollPid = Pid::create(defaultConfigs);

		void setup() {
			// remote.waitForSignal();
			started = true;
		}
		void loop() {
			auto remoteData = Remote::Packet();
			remoteData = remote.getPacketData();
			float percent = (((float)remoteData.pitch - (float)centerOffset) / (float)centerOffset) * (float)45;

			// controllerData.roll = remoteData.roll;
			controllerData.pitch = pitchPid.update<int16_t>(percent, mpu9250.filteredAngles().pitch) + centerOffset;

			// controllerData.pitch = remoteData.pitch;
			controllerData.roll = pitchPid.update<int16_t>(percent, mpu9250.filteredAngles().roll) + centerOffset;

			// printf("pitch: %d\n", controllerData.pitch);
			// printf("roll: %d\n\n", controllerData.roll);

			controllerData.thrust = remoteData.thrust;
			controllerData.yaw = remoteData.yaw;

			int16_t thrust = controllerData.thrust;
			int16_t yaw = controllerData.yaw;
			int16_t pitch = controllerData.pitch;
			int16_t roll = controllerData.roll;

			quadControls.input(std::move(thrust), std::move(yaw), std::move(pitch), std::move(roll));
		}
	} // namespace Core0

	namespace Core1 {

		void setup() {
			Misc::Blink::setup();
		}
		void loop() {
			if (!started) {
				Misc::Blink::start(70);

			} else {
				Misc::Blink::start(250);

				// quadControls.debugPrint();
				mpu9250.debugPrint();
				sleep_ms(50);
				Misc::clearConsole();
			}
		}
	} // namespace Core1

} // namespace Application
