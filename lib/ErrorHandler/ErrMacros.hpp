#ifndef C__PROJECTS_PICO_PICODRONE_LIB_ERRORHANDLER_ERRMACROS_HPP_
#define C__PROJECTS_PICO_PICODRONE_LIB_ERRORHANDLER_ERRMACROS_HPP_

#include "ErrorBlinker.hpp"
// clang-format off

#define ABORT(func) while(true) {func}

#define CHECK_PIN_NUM(pin_num_variable, where, run_this) 	\
	if (pin_num_variable < GPIO_COUNT) { \
		run_this \
	} else { \
		ABORT(LocalLib::ErrorHandler::ErrBlinkSetup(where);)	\
	}

#define CHECK_ADC_PIN(pin_num_variable, where, run_this) 	\
	if (pin_num_variable == 26 || pin_num_variable == 27 || pin_num_variable == 28) { \
		run_this \
	} else { \
		ABORT(LocalLib::ErrorHandler::ErrBlinkSetup(where);) \
	}
// clang-format on

#endif // C__PROJECTS_PICO_PICODRONE_LIB_ERRORHANDLER_ERRMACROS_HPP_