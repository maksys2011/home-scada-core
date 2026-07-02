add_executable(
    tests
    actuator_config_test.cpp
    sensor_config_test.cpp
    modbus_client_test_integration.cpp
    rule_thermostat_test_integration.cpp
    sensor_state_test_unit.cpp
    rule_control_light_integration.cpp
    scada_core_testing_utils.hpp
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