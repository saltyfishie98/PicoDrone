#ifndef C__PROJECTS_PICO_PICODRONE_LIB_HELPERS_NAMESPACE_PICO_HPP_
#define C__PROJECTS_PICO_PICODRONE_LIB_HELPERS_NAMESPACE_PICO_HPP_

#include "pico/mutex.h"

#include "../Types.hpp"

namespace LocalLib::Helpers::Pico {
	class AnalogReader {
	  public:
		static AnalogReader create(const gpioPin_t& number) noexcept;
		uint16_t read() noexcept;
		void debugPrint() const noexcept;

	  private:
		void begin();
		AnalogReader() noexcept {}
		AnalogReader(AnalogReader&&) noexcept {}
		AnalogReader(const AnalogReader&) noexcept {}
		AnalogReader(const gpioPin_t& number) noexcept;

		gpioPin_t m_pinNumber = NULLPIN;
		uint m_input = 4;
		uint16_t m_val = 0;
	};

	namespace Mutex {
		class Mutex {
		  public:
			~Mutex() noexcept;
			static Mutex create() noexcept;

			void lock() noexcept;
			void unlock() noexcept;
			bool entered() noexcept;

		  private:
			Mutex() noexcept {}
			Mutex(Mutex&&) noexcept {}
			Mutex(const Mutex&) noexcept {}
			void begin() noexcept;

			mutex_t m_mtx;
			bool notInit = true;
		};

		class LockGuard {
		  public:
			LockGuard(const LockGuard&) = delete;

			LockGuard(Mutex& mtx) noexcept : m_mtx(mtx) {
				m_mtx.lock();
			}

			~LockGuard() {
				m_mtx.unlock();
			}

		  private:
			Mutex& m_mtx;
		};
	} // namespace Mutex

} // namespace LocalLib::Helpers::Pico

#endif // C__PROJECTS_PICO_PICODRONE_LIB_HELPERS_NAMESPACE_PICO_HPP_