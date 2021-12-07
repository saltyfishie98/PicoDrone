cmake_minimum_required(VERSION 3.13)

set(PICO_SDK_PATH "C:/SDK/pico-sdk")
include(cmake/pico_sdk_import.cmake)

project(PicoDrone C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

option(USE_MULTICORE "use the second core of the rp2040 chip" ON)
option(USE_SANDBOX_ONLY "turn off main program" ON)

include(cmake/set_options.cmake)

pico_sdk_init()
suppress_tinyusb_warnings()

add_subdirectory(lib)

# can't link pico_sdk without doing this
include(src/src.cmake)




