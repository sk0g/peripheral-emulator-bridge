cmake_minimum_required(VERSION 3.22)

set(PICO_SDK_PATH "../../pico-sdk/")
include(pico_sdk_import.cmake)

enable_language(C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

project(main)

add_executable(main main.cpp deviceControl.cpp secondCore.cpp)

target_link_libraries(main pico_stdlib pico_multicore pico_stdio)

pico_sdk_init()

pico_enable_stdio_usb(main 1)
pico_enable_stdio_uart(main 0)

pico_add_extra_outputs(main)
