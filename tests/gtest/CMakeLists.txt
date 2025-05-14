find_package(GTest REQUIRED)

add_executable(testex unit_test.cpp)
target_include_directories(testex PRIVATE ${GTEST_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/tree ${CMAKE_SOURCE_DIR}/graphviz)
target_link_libraries(testex GTest::GTest GTest::Main graphviz_lib)

add_test(NAME gtest_test COMMAND testex)