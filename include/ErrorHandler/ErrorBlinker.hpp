#ifndef C__PROJECTS_PICO_PICODRONE_LIB_ERRORBLINKER_HPP_
#define C__PROJECTS_PICO_PICODRONE_LIB_ERRORBLINKER_HPP_

#include <stdint.h>
#include <array>

#include "Errors.hpp"

namespace PicoPilot::ErrorHandler {
	using ErrorCode = std::array<bool, 16>;
	using ErrorNum = uint16_t;
	using ErrorLocation = uint8_t;
	using ErrorDetail = uint8_t;

	void setErrorLocation(ErrorNum* numAddr, ErrorLocation setType);
	void setErrorType(ErrorNum* numAddr, ErrorDetail setDetail);

	namespace Blinker {
		ErrorCode int2bin(ErrorNum input);
		void printErrorCode(const ErrorCode& input);
		void blink(const ErrorCode& input, const float& speed = 0.5f);
	} // namespace Blinker

	inline void ErrBlinkSetup(ErrorLocation where, ErrorDetail what) {
		ErrorNum errorNum = ERR_NONE;
		setErrorLocation(&errorNum, where);
		setErrorType(&errorNum, what);

		auto errorCode = Blinker::int2bin(errorNum);
		Blinker::printErrorCode(errorCode);
		Blinker::blink(errorCode);
	}
} // namespace PicoPilot::ErrorHandler

#endif // C__PROJECTS_PICO_PICODRONE_LIB_ERRORBLINKER_HPP_