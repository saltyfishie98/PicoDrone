#ifndef C__PROJECTS_PICO_PICODRONE_LIB_HELPERS_NAMESPACE_PICO_HPP_
#define C__PROJECTS_PICO_PICODRONE_LIB_HELPERS_NAMESPACE_PICO_HPP_

#include "pico/mutex.h"

#include "../Types.hpp"
#include "hardware/spi.h"
#include <memory>
#include <array>
#include <algorithm>

#define READ_BIT 0x80

namespace Pico {
	class AnalogReader {
	  public:
		static AnalogReader create(const Pico::gpioPin_t& number) noexcept;
		uint16_t read() noexcept;
		void debugPrint() const noexcept;

	  private:
		void begin();
		AnalogReader() noexcept {}
		AnalogReader(AnalogReader&&) noexcept {}
		AnalogReader(const AnalogReader&) noexcept {}
		AnalogReader(const Pico::gpioPin_t& number) noexcept;

		Pico::gpioPin_t m_pinNumber = NULLPIN;
		uint m_input = 4;
		uint16_t m_val = 0;
	};

	class SPI {
	  public:
		struct Pins {
			gpioPin_t miso = 12;
			gpioPin_t cs = 13;
			gpioPin_t sck = 14;
			gpioPin_t mosi = 15;
		};

		static SPI create(spi_inst_t* port, Pins&& gpioPins) noexcept;

		SPI() = default;

		void cs_select();
		void cs_deselect();
		void read_registers(uint8_t reg, uint8_t* buf, uint16_t len);
		void write_registers(const uint8_t* buf, size_t len);

	  protected:
		SPI(spi_inst_t* port, Pins&& pins) noexcept;
		void begin();
		Pins m_pins;
		spi_inst_t* m_port;

	  private:
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

} // namespace Pico

#endif // C__PROJECTS_PICO_PICODRONE_LIB_HELPERS_NAMESPACE_PICO_HPP_