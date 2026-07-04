cmake_minimum_required(VERSION 3.16)

project(HomeScada VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Paho MQTT options
set(PAHO_WITH_MQTT_C ON CACHE BOOL "" FORCE)
set(PAHO_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(PAHO_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(PAHO_BUILD_DOCUMENTATION OFF CACHE BOOL "" FORCE)

# External dependencies
find_package(nlohmann_json REQUIRED)
find_package(PostgreSQL REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_check_modules(MODBUS REQUIRED libmodbus)

#Google test
include(FetchContent)

enable_testing()

include(GoogleTest)

# Third-party libraries
add_subdirectory(third_party/paho.mqtt.cpp)
add_subdirectory(third_party/googletest)

file(GLOB_RECURSE SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_library(scada_core_lib STATIC ${SRC_FILES})

# Main executable
add_executable(home-scada
    app/main.cpp
    ${SRC_FILES}
)

target_include_directories(scada_core_lib PUBLIC 
    include
    src
    tests
    modbus
    ${PostgreSQL_INCLUDE_DIRS}
    ${MODBUS_INCLUDE_DIRS}
)

target_link_libraries(scada_core_lib PUBLIC
    nlohmann_json::nlohmann_json
    paho-mqttpp3-shared
    ${MODBUS_LINK_LIBRARIES}
)

target_link_libraries(home-scada PRIVATE 
    scada_core_lib
    nlohmann_json::nlohmann_json
    paho-mqttpp3-shared
    ${PostgreSQL_LIBRARIES}
    ${MODBUS_LINK_LIBRARIES}
)

target_compile_options(home-scada PRIVATE ${MODBUS_CFLAGS_OTHER})
target_link_options(home-scada PRIVATE ${MODBUS_LDFLAGS_OTHER})

add_subdirectory(tests)





