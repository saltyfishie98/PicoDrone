#ifndef C__PROJECTS_PICO_PICODRONE_LIB_ERRORHANDLER_ERRMACROS_HPP_
#define C__PROJECTS_PICO_PICODRONE_LIB_ERRORHANDLER_ERRMACROS_HPP_

#include "ErrorBlinker.hpp"
#include "Errors.hpp"

using Predicate = bool;

#define ABORT(func)                                                                                                                             \
	while (true) {                                                                                                                              \
		func                                                                                                                                    \
	}

#define CHECK_ERROR(predicate, errTypes, errDetails, run_this)                                                                                  \
	if (predicate) {                                                                                                                            \
		run_this                                                                                                                                \
	} else {                                                                                                                                    \
		ABORT(LocalLib::ErrorHandler::ErrBlinkSetup(errTypes, errDetails);)                                                                     \
	}

#endif // C__PROJECTS_PICO_PICODRONE_LIB_ERRORHANDLER_ERRMACROS_HPP_