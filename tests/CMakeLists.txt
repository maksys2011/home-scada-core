file(GLOB_RECURSE TESTS_FULES 
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_executable(tests
    ${TESTS_FULES}
)

target_link_libraries(
    tests
    PRIVATE
    GTest::gtest_main
    GTest::gmock_main
    scada_core_lib
)

target_include_directories(
    tests
    PRIVATE
    ../include
    ../src)

gtest_discover_tests(tests)