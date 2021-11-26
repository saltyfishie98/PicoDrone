#ifndef C__PROJECTS_PICO_PICODRONE_LIB_HELPERS_NAMESPACE_PICO_HPP_
#define C__PROJECTS_PICO_PICODRONE_LIB_HELPERS_NAMESPACE_PICO_HPP_

#include "../Core/BaseClass.hpp"
#include "../Types.hpp"

namespace LocalLib::Helpers::Pico {
	class AnalogReader : public BaseClass {
	  public:
		AnalogReader(const GpioPin& number);
		void begin() override;
		uint16_t read();

	  private:
		GpioPin m_pinNumber = NULLPIN;
	};

} // namespace LocalLib::Helpers::Pico

#endif // C__PROJECTS_PICO_PICODRONE_LIB_HELPERS_NAMESPACE_PICO_HPP_