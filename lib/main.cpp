#include "pico/stdlib.h"
#include "pico/multicore.h"

#include <functional>

#define MULTICORE

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

void core1_Process() {
	using namespace Application::Core1;

	setup();
	while (true) {
		loop();
	}
}

int main() {
	stdio_init_all();
	multicore_launch_core1(core1_Process);

	using namespace Application::Core0;

	setup();
	while (true) {
		loop();
	}
}