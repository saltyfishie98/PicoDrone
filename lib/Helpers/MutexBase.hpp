#ifndef C__PROJECTS_PICO_PICODRONE_LIB_HELPERS_MUTEX_HPP_
#define C__PROJECTS_PICO_PICODRONE_LIB_HELPERS_MUTEX_HPP_

#include "../Core/BaseClass.hpp"

namespace LocalLib::Helpers::Pico {
	class IMutex : public BaseClass {
	  public:
		virtual void lock() = 0;
		virtual void unlock() = 0;

	  protected:
		bool notInit = true;
	};
} // namespace LocalLib::Helpers::Pico

#endif // C__PROJECTS_PICO_PICODRONE_LIB_HELPERS_MUTEX_HPP_