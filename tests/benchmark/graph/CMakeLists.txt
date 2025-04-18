add_custom_target(bench_graph
    COMMAND ./bench_graph.sh
            $<TARGET_FILE:benchmarkex>
            ${TEST_FILES_DIR}
            ${CMAKE_SOURCE_DIR}/for_readme
    DEPENDS bench_graph.sh
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_dependencies(bench_graph benchmarkex)