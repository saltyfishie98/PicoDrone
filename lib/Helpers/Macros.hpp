#ifndef C__PROJECTS_PICO_PICODRONE_LIB_HELPERS_MACROS_HPP_
#define C__PROJECTS_PICO_PICODRONE_LIB_HELPERS_MACROS_HPP_

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

#endif // C__PROJECTS_PICO_PICODRONE_LIB_HELPERS_MACROS_HPP_