#include <iostream>
#include <fstream>
#include <vector>
#include <nlohmann/json.hpp>
#include <thread>
#include <chrono>
#include <filesystem>
#include <memory>
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
#include "ConfigLoader.hpp"
#include "RuleConfigLight.hpp"

using json = nlohmann::json;

int main() { 

    std::cout << "Hello === SCADA === \n";
    
    /*
    App ap;
    AppConfig cfg;
    ap.run(std::move(cfg));
    */

    ConfigLoader configPrice;
    configPrice.load();
    AppConfig priceSensor = std::move(configPrice.load());
    for(const auto& sensorCfg : priceSensor.sensorConfigs_){
        sensorCfg.print();
    }

    for(const auto& ruleCfg : priceSensor.ruleConfigs_2){
        ruleCfg->print();
    }




    std::cout << "BYE === SCADA === \n";
    return 0;
}
