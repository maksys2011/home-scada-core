add_executable(
    tests
    actuator_config_test.cpp

    ../src/ActuatorConfig.cpp
    ../src/Enum.cpp
    ../src/utils.cpp
    ../src/RuleConfigLight.cpp
    ../src/RuleThermostatConfig.cpp
    ../src/RuleHumidifierConfig.cpp
    ../src/ModbusSourceConfig.cpp
    ../src/MqttSourceConfig.cpp
    ../src/ModbusActuatorConfig.cpp
    ../src/MqttActuatorConfig.cpp
)

target_link_libraries(
    tests
    PRIVATE
    GTest::gtest_main
    GTest::gmock_main
)

target_include_directories(
    tests
    PRIVATE
    ../include
    ../src)

gtest_discover_tests(tests)