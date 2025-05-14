add_executable(avl avl_main.cpp)
target_include_directories(avl PUBLIC ${CMAKE_SOURCE_DIR}/tree ${CMAKE_SOURCE_DIR}/graphviz)
target_link_libraries(avl PRIVATE graphviz_lib)

add_executable(set stdset_main.cpp)
target_include_directories(set PUBLIC ${CMAKE_SOURCE_DIR}/tree ${CMAKE_SOURCE_DIR}/graphviz)
target_link_libraries(set PRIVATE graphviz_lib)