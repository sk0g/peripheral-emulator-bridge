cmake_minimum_required(VERSION 3.22)

set(PICO_SDK_PATH "../../pico-sdk/")
include(pico_sdk_import.cmake)

enable_language(C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

project(main)

add_executable(main main.cpp)

target_link_libraries(main pico_stdlib)

pico_sdk_init()
pico_add_extra_outputs(main)
