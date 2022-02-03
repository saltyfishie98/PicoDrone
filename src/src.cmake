
# Relative file path used here are relative to the project root directory

set(BINARY_NAME ${PROJECT_NAME})

add_executable(${BINARY_NAME} 
	lib/Core/main.cpp 
	src/PicoDrone.cpp 
)
target_compile_options(${BINARY_NAME} PRIVATE -Wall -Wextra -Wpedantic)

pico_set_program_name(${BINARY_NAME} "${BINARY_NAME}")
pico_set_program_version(${BINARY_NAME} "0.1")

pico_enable_stdio_uart(${BINARY_NAME} 1)
pico_enable_stdio_usb(${BINARY_NAME} 0)

target_include_directories(${BINARY_NAME} PRIVATE 
${PROJECT_SOURCE_DIR}/include 
${PROJECT_SOURCE_DIR}/vendor/pico-lora/src
${PROJECT_SOURCE_DIR}/vendor/FastPID/src)

target_link_libraries(${BINARY_NAME} 
	PwmDevices
	Helpers
	ErrorHandler
	Quad
	MPU9250
	Remote
	Pid
	FastPID

	pico_stdlib 
	hardware_adc
	hardware_pwm
	hardware_i2c
	hardware_spi
	pico_multicore
)

pico_add_extra_outputs(${BINARY_NAME})

add_custom_command(
    TARGET ${BINARY_NAME} POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_BINARY_DIR}/PicoDrone.uf2" "${CMAKE_BINARY_DIR}/../bin/PicoDrone.uf2"
)