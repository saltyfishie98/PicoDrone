#include "pico/stdlib.h"

extern void Application();

int main() {
	stdio_init_all();
	Application();
}