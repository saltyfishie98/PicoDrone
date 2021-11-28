#ifndef C__PROJECTS_PICO_PICODRONE_INCLUDE_PWMDEVICES_HPP_
#define C__PROJECTS_PICO_PICODRONE_INCLUDE_PWMDEVICES_HPP_

#include "../Types.hpp"

namespace LocalLib::Helpers::PwmDevices {
	class PwmFreqConfig {
	  public:
		uint32_t freq = 0;
		uint32_t wrap = 0;
		uint64_t pwmClockSpeed = 0;
		uint pwmSliceNum = 8;

	  protected:
		uint32_t m_pwmClockDiv = 0;

		friend void configureDesiredWrap(PwmFreqConfig* config);
	};

	inline void configureDesiredWrap(PwmFreqConfig* config) {
		assert(config->pwmClockSpeed > 0);

		config->m_pwmClockDiv = config->pwmClockSpeed / config->freq / 4096 +
								(config->pwmClockSpeed % (config->freq * 4096) != 0);

		if (config->m_pwmClockDiv / 16 == 0)
			config->m_pwmClockDiv = 16;

		config->wrap = config->pwmClockSpeed * 16 / config->m_pwmClockDiv / config->freq - 1;
	}

} // namespace LocalLib::Helpers::PwmDevices

#endif // C__PROJECTS_PICO_PICODRONE_INCLUDE_PWMDEVICES_HPP_