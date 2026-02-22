cmake_minimum_required(VERSION 3.16)

project(HomeScada VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Находим библиотеку
find_package(nlohmann_json REQUIRED)

# Исполняемый файл
add_executable(home-scada
    app/main.cpp
    src/Sensor.cpp
    src/SensorConfig.cpp
    src/SensorState.cpp
    src/RandomSource.cpp
    src/Actuator.cpp
    src/ActuatorConfig.cpp
    src/Enum.cpp
    src/Logger.cpp
    src/SensorManager.cpp
    src/Archive.cpp
    tests/tester.cpp
    tests/testSource.cpp
    src/ArchiveReader.cpp
    src/ArchiveReport.cpp
    src/RuleThermostatConfig.cpp
    src/RuleEngine.cpp
    src/App.cpp
    src/ConfigLoader.cpp
    src/RuleConfigLight.cpp
    src/ModbusSource.cpp
    src/ModbusSourceConfig.cpp
    src/utils.cpp
    src/ModbusClient.cpp
)

target_include_directories(home-scada PUBLIC
    include
    src
    tests
    modbus
)

# Добавляем cpp-файлы из src/
file(GLOB SRC_FILES src/*.cpp)
target_sources(home-scada PRIVATE ${SRC_FILES})

# Линкуем JSON-библиотеку
target_link_libraries(home-scada PRIVATE
    nlohmann_json::nlohmann_json
    modbus
)

# Подключаем modbus
find_package(PkgConfig REQUIRED)
pkg_check_modules(MODBUS REQUIRED libmodbus)


add_executable(modbus-test
    tests/modbus_test.cpp
)

target_include_directories(modbus-test PRIVATE ${MODBUS_INCLUDE_DIRS})
target_compile_options(modbus-test PRIVATE ${MODBUS_CFLAGS_OTHER})

target_link_libraries(modbus-test PRIVATE ${MODBUS_LINK_LIBRARIES})
target_link_options(modbus-test PRIVATE ${MODBUS_LDFLAGS_OTHER})






