#include "pico/stdlib.h"
#include "pico/multicore.h"

#include <functional>

void sandbox();

#ifndef ONLY_SANDBOX
namespace Application {
	namespace Core0 {
		void setup();
		void loop();
	} // namespace Core0

	namespace Core1 {
		void setup();
		void loop();
	} // namespace Core1
} // namespace Application

// clang-format off
#ifdef MULTICORE
	#define LAUNCH_CORE_1 multicore_launch_core1(core1_Process)

void core1_Process() {
	using namespace Application::Core1;

	setup();
	while (true) {
		loop();
	}
}

#else
	#define LAUNCH_CORE_1
#endif
// clang-format on

int main() {
	stdio_init_all();

	LAUNCH_CORE_1;

	using namespace Application::Core0;

	setup();
	while (true) {
		loop();
	}
}

#else
int main() {
	stdio_init_all();

	sandbox();
}
#endif