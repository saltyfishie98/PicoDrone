#ifndef C__PROJECTS_PICO_PICODRONE_INCLUDE_INTERFACES_CPP_
#define C__PROJECTS_PICO_PICODRONE_INCLUDE_INTERFACES_CPP_

class IClass {
  public:
	virtual void begin() = 0;
};

class IMutex : public IClass {
  public:
	virtual void lock() = 0;
	virtual void unlock() = 0;

  protected:
	bool notInit = true;
};

#endif // C__PROJECTS_PICO_PICODRONE_INCLUDE_INTERFACES_CPP_