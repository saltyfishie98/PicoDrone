#ifndef C__PROJECTS_PICO_PICODRONE_LIB_HELPERS_MUTEX_HPP_
#define C__PROJECTS_PICO_PICODRONE_LIB_HELPERS_MUTEX_HPP_

#include "IClass.hpp"

class IMutex : public IClass {
  public:
	virtual void lock() = 0;
	virtual void unlock() = 0;

  protected:
	bool notInit = true;
};

#endif // C__PROJECTS_PICO_PICODRONE_LIB_HELPERS_MUTEX_HPP_