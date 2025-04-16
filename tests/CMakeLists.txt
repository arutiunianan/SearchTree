set(TEST_FILES_DIR ${CMAKE_SOURCE_DIR}/tests/test_files)
add_definitions(-DTEST_FILES_DIR="${TEST_FILES_DIR}")
set(ANS_FILES_DIR ${CMAKE_SOURCE_DIR}/ans_files)
add_definitions(-DANS_FILES_DIR="${ANS_FILES_DIR}")

add_subdirectory(e2e)
add_subdirectory(gtest)
add_subdirectory(benchmark)