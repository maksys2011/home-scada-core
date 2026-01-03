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
using json = nlohmann::json;

int main() {

    SensorManager manager;
    const std::string& filePath = "/home/maksys2011/home-scada/configTest.json/SensorConfig.json";
    const std::string& fileLoggerPath = "/home/maksys2011/home-scada/logs/events.log";
    const std::string& fileArchivePath = "/home/maksys2011/home-scada/archive/archive.csv";
    const std::string& file = "/home/maksys2011/home-scada/archive/arch.txt";
    const std::string& fileCfgActuator = "/home/maksys2011/home-scada/configTest.json/ActuatorConfig.json";
    const std::string& fileCfgRuleThermostat = "/home/maksys2011/home-scada/configTest.json/RuleThermostat.json";

    SensorConfig sensorCfg;
    sensorCfg.fromJson(filePath);
    Logger logger(fileLoggerPath);
    Archive archiv(fileArchivePath);
    std::vector<double>values_{18.0, 19.0, 20.0, 21.0, 22.0, 20.0, 18.0, 17.0};
    testSource sourceTemp(values_);
    ActuatorConfig cfgHeater;
    cfgHeater.fromJson(fileCfgActuator);
    Actuator actuator(cfgHeater);
    RuleThermostatConfig thermoConfig;
    thermoConfig.fromJson(fileCfgRuleThermostat);
    Sensor sensor(sensorCfg, &logger, &archiv, &sourceTemp);
    RuleThermostat thermoRule(sensor.state(), actuator, thermoConfig);

    RuleEngine engine;
    engine.addRule(&thermoRule);
    for(auto it : values_){
        
        sensor.update();
        engine.evaluateRules();
    }







    

 
    
    return 0;
}
