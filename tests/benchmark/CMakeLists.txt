find_package(benchmark REQUIRED)

add_executable(benchmarkex benchmark.cpp)
target_link_libraries(benchmarkex PUBLIC benchmark::benchmark graphviz_lib)
target_include_directories(benchmarkex PRIVATE ${CMAKE_SOURCE_DIR}/tree ${CMAKE_SOURCE_DIR}/graphviz)

add_subdirectory(graph)