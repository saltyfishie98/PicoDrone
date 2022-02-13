#ifndef C__PROJECTS_PICO_PICODRONE_LIB_HELPERS_HPP_
#define C__PROJECTS_PICO_PICODRONE_LIB_HELPERS_HPP_

#include "Types.hpp"
#include "pico/stdlib.h"
#include "stdio.h"
#include "Helpers/Macros.hpp"

namespace PicoPilot::Misc {

	namespace Blink {
		void run(uint interval) noexcept;
		void setup() noexcept;
	} // namespace Blink

	namespace Kalman {
		struct Configs {
			float R = 7000.f;
			float H = 1.f;
			float Q = 10.f;
			float P = 0.f;
			float UHat = 0.f;
			float K = 0.f;
		};

		inline float filter(Configs& configs, const float& U) noexcept {
			configs.K = configs.P * configs.H / (configs.H * configs.P * configs.H + configs.R);
			configs.UHat = configs.UHat + configs.K * (U - configs.H * configs.UHat);
			configs.P = (1.f - configs.K * configs.H) * configs.P + configs.Q;

			return configs.UHat;
		}
	} // namespace Kalman

	namespace Complementary {
		inline float filter(float fraction, float part0, float part1) noexcept {
			return (fraction * (part0)) + ((1 - fraction) * part1);
		}
	} // namespace Complementary

	template <typename T>
	bool arrayFind(T thisElement, T inThisArray) noexcept {
		T* condition = std::find(std::begin(inThisArray), std::end(inThisArray), thisElement);
		if (condition != std::end(inThisArray))
			return true;
		return false;
	}

	template <typename T>
	inline T milli(const T& value) noexcept {
		T out = (float)value * 1000.f;
		return out;
	}

	inline void clearConsole() {
		DEBUG_RUN(printf("\033[2J");)
	}

} // namespace PicoPilot::Misc

#endif // C__PROJECTS_PICO_PICODRONE_LIB_HELPERS_HPP_
