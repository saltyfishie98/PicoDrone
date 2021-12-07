#ifndef C__PROJECTS_PICO_PICODRONE_INCLUDE_I2C_I2C_HPP_
#define C__PROJECTS_PICO_PICODRONE_INCLUDE_I2C_I2C_HPP_

#include "pico"

namespace LocalLib {
	class I2CComms {
	  public:
	  private:
		uint8_t m_devAddr = 0;
	};
} // namespace LocalLib

#endif // C__PROJECTS_PICO_PICODRONE_INCLUDE_I2C_I2C_HPP_