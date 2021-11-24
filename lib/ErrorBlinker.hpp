#ifndef C__PROJECTS_PICO_PICODRONE_LIB_ERRORBLINKER_HPP_
#define C__PROJECTS_PICO_PICODRONE_LIB_ERRORBLINKER_HPP_

#include <stdint.h>
#include <array>

namespace LocalLib::ErrorBlinker {
	using ErrorCode = std::array<bool, 10>;

	ErrorCode int2bin(uint8_t input);
	void printErrorCode(const ErrorCode& input);
	void blink(const ErrorCode& input, const float& speed = 0.5f);

} // namespace LocalLib::ErrorBlinker

#endif // C__PROJECTS_PICO_PICODRONE_LIB_ERRORBLINKER_HPP_