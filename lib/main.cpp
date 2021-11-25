#include "pico/stdlib.h"

extern void sandbox();
namespace Application {
	extern void setup();
	extern void loop();
} // namespace Application

int main() {
	stdio_init_all();
	using namespace Application;

	setup();

	while (true) {
		loop();
	}

	// sandbox();
}