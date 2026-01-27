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
    FilePath paths;
    paths.fileSensorConfigPath =  "/home/maksys2011/scada-core/home-scada-core/configTest.json/SensorConfig.json";
    paths.fileLoggerPath =        "/home/maksys2011/scada-core/home-scada-core/logs/events.log";
    paths.fileArchivePath =       "/home/maksys2011/scada-core/home-scada-core/archive/archive.csv";
    paths.fileCfgActuator =       "/home/maksys2011/scada-core/home-scada-core/configTest.json/ActuatorConfig.json";
    paths.fileCfgRuleThermostat = "/home/maksys2011/scada-core/home-scada-core/configTest.json/RuleThermostat.json";

    
    return 0;
}
