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

using json = nlohmann::json;

int main() {

    SensorManager manager;
    const std::string& filePath = "/home/maksys2011/home-scada/configTest.json/SensorConfig.json";
    const std::string& fileLoggerPath = "/home/maksys2011/home-scada/logs/events.log";
    const std::string& fileArchivePath = "/home/maksys2011/home-scada/archive/archive.csv";
    const std::string& file = "/home/maksys2011/home-scada/archive/arch.txt";
    const std::string& fileCfgActuator = "/home/maksys2011/home-scada/configTest.json/ActuatorConfig.json";
    const std::string& fileCfgRuleThermostat = "/home/maksys2011/home-scada/configTest.json/RuleThermostat.json";

    RuleThermostatConfig cfgT;
    cfgT.fromJson(fileCfgRuleThermostat);
    cfgT.print();



    

 
    
    return 0;
}
