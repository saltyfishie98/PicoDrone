# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(PICO_SDK_PATH "C:/SDK/pico-sdk")

include(pico_sdk_import.cmake)
project(PicoDroneProj C CXX ASM)

option(USE_MULTICORE "use the second core of the rp2040 chip" ON)

if(USE_MULTICORE)
	add_compile_definitions(MULTICORE)
	message(STATUS "")
	message(STATUS "multicore program")
	message(STATUS "")
endif()

pico_sdk_init()
suppress_tinyusb_warnings()

add_subdirectory(lib)

add_executable(PicoDrone lib/main.cpp PicoDrone.cpp sandbox.cpp)
target_compile_options(PicoDrone PRIVATE -Wall -Wextra -Wpedantic)

pico_set_program_name(PicoDrone "PicoDrone")
pico_set_program_version(PicoDrone "0.1")

pico_enable_stdio_uart(PicoDrone 1)
pico_enable_stdio_usb(PicoDrone 0)

target_link_libraries(PicoDrone 
	PwmDevices
	Helpers
	ErrorHandler

	pico_stdlib 
	hardware_adc
	hardware_pwm
	pico_multicore
)

pico_add_extra_outputs(PicoDrone)

add_custom_command(
    TARGET PicoDrone POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_BINARY_DIR}/PicoDrone.uf2" "${CMAKE_BINARY_DIR}/../bin/PicoDrone.uf2"
)


