#include "ErrorHandler/ErrorBlinker.hpp"

#include <iostream>
#include "pico/stdlib.h"
#include "Types.hpp"
#include "Helpers/Macros.hpp"

namespace PicoPilot::ErrorHandler {
	void setErrorLocation(ErrorNum* numAddr, ErrorLocation setType) {
		(*numAddr) |= (1 << (setType - 1));
	}

	void setErrorType(ErrorNum* numAddr, ErrorDetail setDetail) {
		(*numAddr) |= ((1 << (setDetail - 1)) << 8);
	}

	namespace Blinker {
		ErrorCode int2bin(ErrorNum input) {
			ErrorCode binArray;
			for (std::size_t i = 0; i < binArray.size(); i++) {
				binArray[i] = input % 2;
				input /= 2;
			}
			return binArray;
		}

		void printErrorCode(const ErrorCode& input) {
			std::cout << "Error Code: ";
			for (int i = input.size() - 1; i >= 0; i--) {
				std::cout << input[i];
			}
			std::cout << '\n';
		}

		class BlinkerLed {
		  public:
			BlinkerLed(const Pico::gpioPin_t& number = PICO_DEFAULT_LED_PIN) : m_pinNum(number) {
				gpio_init(m_pinNum);
				gpio_set_dir(m_pinNum, 1);
				DEBUG_RUN(std::cout << "\n\n================== created Blicker =================\n\n";)
			}

			void setSpeed(const float& speed) {
				m_scale = 1 / speed;
			}

			void startBlink() {
				gpio_put(m_pinNum, 1);
				sleep_ms(50 * m_scale);
				gpio_put(m_pinNum, 0);
				sleep_ms(50 * m_scale);
				gpio_put(m_pinNum, 1);
				sleep_ms(50 * m_scale);
				gpio_put(m_pinNum, 0);
				sleep_ms(50 * m_scale);
				gpio_put(m_pinNum, 1);
				sleep_ms(50 * m_scale);
				gpio_put(m_pinNum, 0);
				sleep_ms(450 * m_scale);
			}

			void shortBlink() {
				gpio_put(m_pinNum, 1);
				sleep_ms(shortInterval * m_scale);
				gpio_put(m_pinNum, 0);
				sleep_ms(spaceInterval * m_scale);
			}

			void longBlink() {
				gpio_put(m_pinNum, 1);
				sleep_ms(longInterval * m_scale);
				gpio_put(m_pinNum, 0);
				sleep_ms(spaceInterval * m_scale);
			}

		  private:
			uint32_t shortInterval = 100;
			uint32_t longInterval = 400;
			uint32_t spaceInterval = 600;
			float m_scale = 1.f;
			Pico::gpioPin_t m_pinNum = NULLPIN;
		} errorLed;

		void blink(const ErrorCode& input, const float& speed) {
			errorLed.setSpeed(speed);

			errorLed.startBlink();

			for (int i = input.size() - 1; i >= 0; i--) {
				if (input[i] == 1) {
					errorLed.longBlink();
				} else {
					errorLed.shortBlink();
				}
			}

			sleep_ms(400);
		}
	} // namespace Blinker
} // namespace PicoPilot::ErrorHandler