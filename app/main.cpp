#include <iostream>
#include <fstream>
#include <vector>
#include <nlohmann/json.hpp>
#include <thread>
#include <chrono>
#include "SensorConfig.hpp"
#include "ActuatorConfig.hpp"
#include "Actuator.hpp"
#include "Sensor.hpp"
#include "RandomSource.hpp"
#include "Logger.hpp"
#include "Archive.hpp"
#include "SensorManager.hpp"
#include "SmoothRandomSource.hpp"
using json = nlohmann::json;

int main() {

    Logger log("../logs/events.log");
    Archive arch("/home/maksys2011/home-scada/archive/archive.csv");
    SensorConfig cfg;
    const std::string filePath("/home/maksys2011/home-scada/configTest.json/SensorConfig.json");
    cfg.fromJson(filePath);
    SensorState state(cfg, &log, &arch);
    SmothRandomSource source(22.0,0.2,15,30);


    for(int i = 0; i < 50; i++){
        state.processValue(source.readValue());
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    std::cout << "test 11 " << std::endl;




}
