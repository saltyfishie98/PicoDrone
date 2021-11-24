#ifndef C__PROJECTS_PICO_PICODRONE_LIB_TYPES_HPP_
#define C__PROJECTS_PICO_PICODRONE_LIB_TYPES_HPP_

#include <stdint.h>

#define NULLPIN	   31
#define GPIO_COUNT NUM_BANK0_GPIOS

namespace LocalLib {
	using GpioPin = uint8_t;
} // namespace LocalLib

#endif // C__PROJECTS_PICO_PICODRONE_LIB_TYPES_HPP_