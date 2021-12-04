#ifndef C__PROJECTS_PICO_PICODRONE_LIB_TYPES_HPP_
#define C__PROJECTS_PICO_PICODRONE_LIB_TYPES_HPP_

#include <pico/types.h>
#include <stdint.h>
#include <functional>

#define NULLPIN		   31
#define GPIO_PIN_COUNT 29

namespace LocalLib {
	using gpioPin_t = uint8_t;
	using millis_t = uint32_t;

	using pwm_t = unsigned int;
	using pwmWrap_t = uint16_t;

} // namespace LocalLib

#endif // C__PROJECTS_PICO_PICODRONE_LIB_TYPES_HPP_