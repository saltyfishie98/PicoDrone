#ifndef C__PROJECTS_PICO_PICODRONE_LIB_HELPERS_HPP_
#define C__PROJECTS_PICO_PICODRONE_LIB_HELPERS_HPP_

#ifndef NDEBUG
	#define DEBUG_RUN(func) func
#else
	#define DEBUG_RUN(func)
#endif

namespace LocalLib {
	namespace Helpers {
		namespace Arduino {
			template <typename T>
			T map(T x, T in_min, T in_max, T out_min, T out_max) {
				return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
			}
		} // namespace Arduino
	}	  // namespace Helpers
} // namespace LocalLib

#endif // C__PROJECTS_PICO_PICODRONE_LIB_HELPERS_HPP_