add_executable(avl avl_main.cpp)
target_include_directories(avl PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_executable(set stdset_main.cpp)
target_include_directories(set PUBLIC ${CMAKE_SOURCE_DIR}/include)