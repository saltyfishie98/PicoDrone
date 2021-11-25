#ifndef C__PROJECTS_PICO_PICODRONE_LIB_ERRORBLINKER_HPP_
#define C__PROJECTS_PICO_PICODRONE_LIB_ERRORBLINKER_HPP_

#include <stdint.h>
#include <array>

#define BLK_PIN_ERR 1
#define BLK_ADC_ERR 2
#define BLK_PWM_ERR 4

#define BLK_PIN_EXCEED 1
#define BLK_UNDEFINED  2

namespace LocalLib::ErrorBlinker {
	using ErrorCode = std::array<bool, 16>;
	using ErrorNum = uint16_t;
	using ErrorType = uint8_t;
	using ErrorDetail = uint8_t;

	void setErrorType(ErrorNum* numAddr, ErrorType setType);
	void setErrorDetail(ErrorNum* numAddr, ErrorDetail setDetail);

	ErrorCode int2bin(ErrorNum input);
	void printErrorCode(const ErrorCode& input);
	void blink(const ErrorCode& input, const float& speed = 0.5f);

} // namespace LocalLib::ErrorBlinker

#endif // C__PROJECTS_PICO_PICODRONE_LIB_ERRORBLINKER_HPP_