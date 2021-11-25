#include "pico/stdlib.h"
#include "pico/multicore.h"

namespace Application {
	namespace Core0 {
		extern void setup();
		extern void loop();
	} // namespace Core0

#ifdef MULTICORE
	namespace Core1 {
		extern void setup();
		extern void loop();
	} // namespace Core1
#endif
} // namespace Application

#ifdef MULTICORE
void core1_main() {
	using namespace Application::Core1;

	setup();

	while (true) {
		loop();
	}
}
#endif

int main() {
	stdio_init_all();

#ifdef MULTICORE
	multicore_launch_core1(core1_main);
#endif

	using namespace Application::Core0;

	setup();

	while (true) {
		loop();
	}
}