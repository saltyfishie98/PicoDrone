#ifndef C__PROJECTS_PICO_PICODRONE_LIB_HELPERS_NAMESPACE_PICO_HPP_
#define C__PROJECTS_PICO_PICODRONE_LIB_HELPERS_NAMESPACE_PICO_HPP_

#include "pico/mutex.h"

#include "../Types.hpp"
#include "hardware/spi.h"
#include <memory>
#include <array>
#include <algorithm>

#define SPI_PORT spi0

namespace LocalLib::Pico {
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

	class SPI {
	  public:
		static SPI create(uint&& miso = 4, uint&& cs = 5, uint&& sck = 6, uint&& mosi = 7) noexcept;

		SPI() = default;
		SPI(uint&& miso, uint&& cs, uint&& sck, uint&& mosi) noexcept;

		void begin();
		void csSelect() noexcept;
		void csDeselect() noexcept;
		void writeRegister(uint8_t* buffer, std::size_t len) noexcept;
		void readRegister(uint8_t&& reg, uint8_t* buffer, std::size_t len) noexcept;

	  private:
		uint m_miso = 0;
		uint m_cs = 0;
		uint m_sck = 0;
		uint m_mosi = 0;
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

} // namespace LocalLib::Pico

#endif // C__PROJECTS_PICO_PICODRONE_LIB_HELPERS_NAMESPACE_PICO_HPP_