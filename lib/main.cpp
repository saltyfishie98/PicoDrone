#include "pico/stdlib.h"

extern void Application();
extern void sandbox();

int main() {
	stdio_init_all();
	Application();
	// sandbox();
}