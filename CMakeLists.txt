cmake_minimum_required(VERSION 3.16)

project(open CXX ASM)

include(CTest)
set(CMAKE_CXX_STANDARD 20)

find_package(fmt CONFIG REQUIRED)

add_subdirectory(transmogrify)
add_subdirectory(tests)
add_subdirectory(example)

