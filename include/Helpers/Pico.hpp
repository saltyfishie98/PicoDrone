#ifndef C__PROJECTS_PICO_PICODRONE_LIB_HELPERS_NAMESPACE_PICO_HPP_
#define C__PROJECTS_PICO_PICODRONE_LIB_HELPERS_NAMESPACE_PICO_HPP_

#include "pico/mutex.h"

#include "../Bases/Interfaces/IClass.hpp"
#include "../Bases/Interfaces/IMutex.hpp"
#include "../Types.hpp"

namespace LocalLib::Helpers::Pico {
	class AnalogReader : public IClass {
	  public:
		AnalogReader(const GpioPin& number);
		void begin() override;
		uint16_t read();

	  private:
		GpioPin m_pinNumber = NULLPIN;
	};

	namespace Mutex {
		class BasicMutex : public IMutex {
		  public:
			BasicMutex();
			~BasicMutex();

			void begin() override;
			void lock() override;
			void unlock() override;
			void runIfOwned(const VoidCallback& thisStdFunction);

		  private:
			mutex_t m_mtx;
		};

		class LockGuard {
		  public:
			LockGuard(const LocalLib::Helpers::Pico::Mutex::LockGuard&) = delete;

			LockGuard(IMutex* mtx) : m_mtx(mtx) {
				m_mtx->lock();
			}

			~LockGuard() {
				m_mtx->unlock();
			}

		  private:
			IMutex* m_mtx;
		};
	} // namespace Mutex

} // namespace LocalLib::Helpers::Pico

#endif // C__PROJECTS_PICO_PICODRONE_LIB_HELPERS_NAMESPACE_PICO_HPP_