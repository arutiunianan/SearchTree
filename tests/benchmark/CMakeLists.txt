find_package(benchmark REQUIRED)

add_executable(benchmarkex benchmark.cpp)
target_link_libraries(benchmarkex PUBLIC benchmark::benchmark)
target_include_directories(benchmarkex PRIVATE ${CMAKE_SOURCE_DIR}/include)

add_subdirectory(graph)