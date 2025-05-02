find_package(GTest REQUIRED)

add_executable(testex unit_test.cpp)
target_include_directories(testex PRIVATE ${GTEST_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(testex GTest::GTest GTest::Main)

add_test(NAME gtest_test COMMAND testex)