cmake_minimum_required(VERSION 3.10)

project(searchtree)

add_compile_options(
    -Wall
    -Wextra
    -Wpedantic
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

add_executable(tree main.cpp source/tree.cpp)
target_include_directories(tree PUBLIC include)

enable_testing()
add_subdirectory(tests)