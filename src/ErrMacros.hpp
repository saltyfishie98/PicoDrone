#ifndef C__PROJECTS_PICO_PICODRONE_LIB_ERRORHANDLER_ERRMACROS_HPP_
#define C__PROJECTS_PICO_PICODRONE_LIB_ERRORHANDLER_ERRMACROS_HPP_

#include "ErrorHandler/ErrorBlinker.hpp"
#include "ErrorHandler/Errors.hpp"
#include "Types.hpp"

#include <string>

using Predicate = bool;

template <bool b>
struct StaticAssert {};

// template specialized on true
template <>
struct StaticAssert<true> {
	static void Assert() {}
};

#define ABORT(func)                                                                                                         \
	while (true) {                                                                                                          \
		func                                                                                                                \
	}

#define CHECK_ERROR(predicate, errTypes, errDetails, run_this)                                                              \
	if (predicate) {                                                                                                        \
		run_this                                                                                                            \
	} else {                                                                                                                \
		ABORT(PicoPilot::ErrorHandler::ErrBlinkSetup(errTypes, errDetails);)                                                \
	}

#endif // C__PROJECTS_PICO_PICODRONE_LIB_ERRORHANDLER_ERRMACROS_HPP_