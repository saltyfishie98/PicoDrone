#ifndef C__PROJECTS_PICO_PICODRONE_LIB_TYPES_HPP_
#define C__PROJECTS_PICO_PICODRONE_LIB_TYPES_HPP_

#include <pico/types.h>
#include <stdint.h>
#include <functional>

#define NULLPIN	   31
#define GPIO_COUNT NUM_BANK0_GPIOS

namespace LocalLib {
	using GpioPin_t = uint8_t;
	using Millis_t = uint32_t;
	using PwmWrap_t = uint32_t;

	using VoidCallback = std::function<void()>;
} // namespace LocalLib

#endif // C__PROJECTS_PICO_PICODRONE_LIB_TYPES_HPP_