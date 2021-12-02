#ifndef C__PROJECTS_PICO_PICODRONE_LIB_HELPERS_NAMESPACE_PICO_HPP_
#define C__PROJECTS_PICO_PICODRONE_LIB_HELPERS_NAMESPACE_PICO_HPP_

#include "pico/mutex.h"

#include "../Interfaces.hpp"
#include "../Types.hpp"

namespace LocalLib::Helpers::Pico {
	class AnalogReader {
	  public:
		static AnalogReader factory(const gpioPin_t& number);
		uint16_t read();

	  private:
		void begin();
		AnalogReader() {}
		AnalogReader(AnalogReader&&) {}
		AnalogReader(const AnalogReader&) {}
		AnalogReader(const gpioPin_t& number);

		gpioPin_t m_pinNumber = NULLPIN;
	};

	namespace Mutex {
		class BasicMutex : public IMutex {
		  public:
			~BasicMutex();
			static BasicMutex factory();

			void lock() override;
			void unlock() override;
			void runIfOwned(const VoidCallback& thisStdFunction);

		  private:
			BasicMutex() {}
			BasicMutex(BasicMutex&&) {}
			BasicMutex(const BasicMutex&) {}
			void begin() override;

			mutex_t m_mtx;
		};

		class LockGuard {
		  public:
			LockGuard(const LockGuard&) = delete;

			LockGuard(IMutex& mtx) : m_mtx(mtx) {
				m_mtx.lock();
			}

			~LockGuard() {
				m_mtx.unlock();
			}

		  private:
			IMutex& m_mtx;
		};
	} // namespace Mutex

} // namespace LocalLib::Helpers::Pico

#endif // C__PROJECTS_PICO_PICODRONE_LIB_HELPERS_NAMESPACE_PICO_HPP_