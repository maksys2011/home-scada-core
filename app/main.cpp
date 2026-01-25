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
#include "testSource.hpp"
#include "ArchiveReader.hpp"
#include "ArchiveReport.hpp"
#include "RuleThermostatConfig.hpp"
#include "RuleEngine.hpp"
#include "RuleThermostat.hpp"
#include "App.hpp"
using json = nlohmann::json;

int main() {
    App ap;
    ap.run();
    std::string cmd;
    std::cin >> cmd;
    std::cout << cmd << std::endl;
    ap.repl(cmd);
    
    return 0;
}
