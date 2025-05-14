cmake_minimum_required(VERSION 3.10)

project(searchtree)

add_compile_options(
    -Werror
    -Wall
    -Wextra
    -Wpedantic
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

add_subdirectory(graphviz)

add_executable(tree main.cpp)
target_include_directories(tree PUBLIC tree)
target_link_libraries(tree PRIVATE graphviz_lib)

enable_testing()
add_subdirectory(tests)