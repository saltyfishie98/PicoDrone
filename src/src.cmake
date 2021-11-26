
# Relative file path used here are relative to the project root directory

set(BINARY_NAME ${PROJECT_NAME})

add_executable(${BINARY_NAME} 
	lib/main.cpp 
	src/PicoDrone.cpp 
	src/sandbox.cpp
)
target_compile_options(${BINARY_NAME} PRIVATE -Wall -Wextra -Wpedantic)

pico_set_program_name(${BINARY_NAME} "${BINARY_NAME}")
pico_set_program_version(${BINARY_NAME} "0.1")

pico_enable_stdio_uart(${BINARY_NAME} 1)
pico_enable_stdio_usb(${BINARY_NAME} 0)

include_directories(${PROJECT_SOURCE_DIR})

target_link_libraries(${BINARY_NAME} 
	Pwm50Devices
	Helpers
	ErrorHandler

	pico_stdlib 
	hardware_adc
	hardware_pwm
	pico_multicore
)

pico_add_extra_outputs(${BINARY_NAME})

add_custom_command(
    TARGET ${BINARY_NAME} POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_BINARY_DIR}/PicoDrone.uf2" "${CMAKE_BINARY_DIR}/../bin/PicoDrone.uf2"
)