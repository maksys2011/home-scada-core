#include <iostream>
#include <fstream>
#include <vector>
#include <nlohmann/json.hpp>
#include "SensorConfig.hpp"
#include "ActuatorConfig.hpp"
#include "Actuator.hpp"
#include "Sensor.hpp"
#include "RandomSource.hpp"
#include "Logger.hpp"
using json = nlohmann::json;

int main() {

    const std::string path = "/home/maksys2011/home-scada/configTest.json/Test_sensor.json";
    SensorConfig cfg;
    cfg.fromJson(path);
    Logger log;
    SensorState state(cfg, &log);
    std::vector<double>val = {
    25, 26, 27,        // OK
    29, 30, 31,        // OK → WARN (через debounce)
    30, 29, 28,        // WARN держится (гистерезис)
    27,                // OK
    38, 39, 40, 41,    // WARN → ALARM
    40, 39, 38,        // ALARM держится
    37                 // WARN
};
    for(const double v : val){
        state.processValue(v);
    }

    

    return 0;
}
