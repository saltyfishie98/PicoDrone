#ifndef C__PROJECTS_PICO_PICODRONE_LIB_HELPERS_MACROS_HPP_
#define C__PROJECTS_PICO_PICODRONE_LIB_HELPERS_MACROS_HPP_

#include <stdio.h>

#define PRINT_DEBUG
#define ANALOG_MAX 4095

#ifdef PRINT_DEBUG
	#ifndef NDEBUG
		#define DEBUG_RUN(func) func
	#else
		#define DEBUG_RUN(func)
	#endif
#else
	#define DEBUG_RUN(func)
#endif

#endif // C__PROJECTS_PICO_PICODRONE_LIB_HELPERS_MACROS_HPP_