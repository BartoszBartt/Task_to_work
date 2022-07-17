cmake_minimum_required(VERSION 3.20)
project(cpp)

set(CMAKE_CXX_STANDARD 14)
add_compile_options(-Wno-unused-variable -Wno-unused-parameter -Wall -Wextra -Werror -Wpedantic -pedantic-errors -Wconversion)

set(TARGET colors)

set(SRCS
    include/colors.hpp
    src/main.cpp
)

add_executable(${TARGET} ${SRCS})
target_include_directories(${TARGET} PUBLIC include)
