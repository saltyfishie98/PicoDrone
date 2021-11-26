#include "../Pwm50Devices.hpp"

#include <iostream>

#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"

#include "../Helpers.hpp"
#include "../ErrorHandler.hpp"
#include "../Types.hpp"

namespace LocalLib::Pwm50Devices {
	void Pwm50Devices::setGpioPin(const uint8_t& gpioPinNumber) {
		servoPin = gpioPinNumber;
	}

	void Pwm50Devices::begin() {
		CHECK_ERROR(servoPin < GPIO_COUNT, ERR_PWM, ERR_DT_GPIO_PIN_NUM_EXCEED, {
			gpio_set_function(servoPin, GPIO_FUNC_PWM);
			uint slice_num = pwm_gpio_to_slice_num(servoPin);

			pwm_config config = pwm_get_default_config();
			uint64_t clockspeed = clock_get_hz(clk_sys);
			clockDiv = 64;
			wrap = 39062;

			while (clockspeed / clockDiv / 50 > 65535 && clockDiv < 256) {
				clockDiv += 64;
			}

			wrap = clockspeed / clockDiv / 50;

			pwm_config_set_clkdiv(&config, clockDiv);
			pwm_config_set_wrap(&config, wrap);

			pwm_init(slice_num, &config, true);
		});
	}

	void Pwm50Devices::setPercent(const float& percent) {
		CHECK_ERROR(percent < 1.f, ERR_PWM, ERR_DT_PWM_INVALID_PERCENT, {
			using namespace Helpers;
			float millis = Arduino::map(percent, 0.f, 1.f, 400.f, 2400.f);
			// DEBUG_RUN(std::cout << "millis: " << millis << "\n\n";)
			pwm_set_gpio_level(servoPin, (millis / 20000.f) * wrap);
		});
	}
} // namespace LocalLib::Pwm50Devices