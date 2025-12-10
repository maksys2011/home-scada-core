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
    const std::string file = "../configTest.json/SensorConfig.json";
    SensorConfig s;
    s.fromJson(file);
    s.print();

    std::cout << "-----------------" << std::endl;

    const std::string file2 = "../configTest.json/ActuatorConfig.json";
    ActuatorConfig a;
    a.fromJson(file2);
    a.print();
    std::cout << std::endl;

    const Actuator motor(a);
    motor.print();

    std::cout << std::endl;

    Sensor sensor(s);
    sensor.updateValue(55);
    sensor.print();

    RandomSource scr(0, 100);
    for (int i = 0; i < 10; i++) {
        std::cout << scr.readValue() << std::endl;
    }

    std::cout << "TEST 7" << std::endl;


    return 0;
}
