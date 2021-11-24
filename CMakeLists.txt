# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(PICO_SDK_PATH "C:/SDK/pico-sdk")

include(pico_sdk_import.cmake)
project(PicoDroneProj C CXX ASM)

pico_sdk_init()

add_subdirectory(lib)

add_executable(PicoDrone lib/main.cpp PicoDrone.cpp)

pico_set_program_name(PicoDrone "PicoDrone")
pico_set_program_version(PicoDrone "0.1")

pico_enable_stdio_uart(PicoDrone 1)
pico_enable_stdio_usb(PicoDrone 0)

target_link_libraries(PicoDrone 
	PwmDevices
	Helpers

	pico_stdlib 
	hardware_adc
	hardware_pwm
)

pico_add_extra_outputs(PicoDrone)

add_custom_command(
    TARGET PicoDrone POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_BINARY_DIR}/PicoDrone.uf2" "${CMAKE_BINARY_DIR}/../bin/PicoDrone.uf2"
)


