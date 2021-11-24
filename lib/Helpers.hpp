#ifndef C__PROJECTS_PICO_PICODRONE_LIB_HELPERS_HPP_
#define C__PROJECTS_PICO_PICODRONE_LIB_HELPERS_HPP_

#include "Types.hpp"

#ifndef NDEBUG
	#define DEBUG_RUN(func) func
#else
	#define DEBUG_RUN(func)
#endif

// clang-format off
#define CHECK_PIN_NUM(pin_num_variable, error_code, run_this) 	\
	if (pin_num_variable < GPIO_COUNT) { \
		run_this \
	} else { \
		std::cout << "Error Code: " << error_code << "\n"; \
		std::abort(); \
	}
// clang-format on

namespace LocalLib {
	namespace Helpers {
		namespace Arduino {
			template <typename T>
			T map(T x, T in_min, T in_max, T out_min, T out_max) {
				return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
			}
		} // namespace Arduino

		namespace Pico {
			class AnalogReader {
			  public:
				AnalogReader();
				const uint16_t getVal();

			  private:
				GpioPin m_pinNumber = NULLPIN;
			};
		} // namespace Pico
	}	  // namespace Helpers
} // namespace LocalLib

#endif // C__PROJECTS_PICO_PICODRONE_LIB_HELPERS_HPP_