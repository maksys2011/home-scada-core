#include <iostream>
#include <fstream>
#include <vector>
#include <nlohmann/json.hpp>
#include "SensorConfig.hpp"
#include "ActuatorConfig.hpp"
#include "Actuator.hpp"
#include "Sensor.hpp"
#include "RandomSource.hpp"
using json = nlohmann::json;

int main() {

    const std::string path = "/home/maksys2011/home-scada/configTest.json/SensorConfig.json";
    SensorConfig config;
    Sensor sensor(config);
    sensor.print();
    config.print();

    return 0;
}
