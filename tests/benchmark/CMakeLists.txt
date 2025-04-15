find_package(benchmark REQUIRED)

add_executable(benchmarkex benchmark.cpp ${CMAKE_SOURCE_DIR}/source/tree.cpp)
target_link_libraries(benchmarkex PUBLIC benchmark::benchmark)
target_include_directories(benchmarkex PRIVATE ${CMAKE_SOURCE_DIR}/include )