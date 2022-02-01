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

	const int16_t centerOffset = 511;
	bool started = false;
	auto controllerData = Remote::Packet();
	auto mtx = Pico::Mutex::Mutex::create();

	namespace Core0 {
		auto defaultPins = Pico::SPI::Pins();
		auto defaultConfigs = Pid::Configs();

		auto pitchPid = Pid::create(defaultConfigs);
		auto rollPid = Pid::create(defaultConfigs);
		auto mpu9250 = Mpu9250::create(spi1, std::move(defaultPins), 100);
		auto remote = Remote::create();

		void setup() {
			remote.waitForSignal();
			started = true;
		}
		void loop() {
			auto remoteData = Remote::Packet();
			remoteData = remote.getPacketData();
			float percent = (((float)remoteData.pitch - (float)centerOffset) / (float)centerOffset) * (float)45;

			mtx.lock();
			// controllerData.roll = 511;
			controllerData.pitch = pitchPid.update<int16_t>(percent, mpu9250.filteredAngles().pitch) + centerOffset;
			controllerData.roll = rollPid.update<int16_t>(percent, mpu9250.filteredAngles().roll) + centerOffset;
			controllerData.thrust = remoteData.thrust;
			controllerData.yaw = remoteData.yaw;
			mtx.unlock();

			// printf("\n");
		}
	} // namespace Core0

	namespace Core1 {
		auto quadControls = Quad::Controls::create({6, 7, 8, 9});

		void setup() {
			Misc::Blink::setup();
		}
		void loop() {
			if (!started) {
				Misc::Blink::start(70);

			} else {
				mtx.lock();
				int16_t thrust = controllerData.thrust;
				int16_t yaw = controllerData.yaw;
				int16_t pitch = controllerData.pitch;
				int16_t roll = controllerData.roll;
				mtx.unlock();

				quadControls.input(std::move(thrust), std::move(yaw), std::move(pitch), std::move(roll));
				Misc::Blink::start(250);

				// quadControls.debugPrint();
				// printf("\n");
			}
		}
	} // namespace Core1

} // namespace Application
