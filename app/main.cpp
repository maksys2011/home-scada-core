#include <iostream>
#include <fstream>
#include <vector>
#include <nlohmann/json.hpp>
#include <thread>
#include <chrono>
#include <filesystem>
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
#include "LightConfig.hpp"

using json = nlohmann::json;

int main() { 

    std::cout << "Hello === SCADA === \n";
    App ap;
    AppConfig cfg;
    ap.run(std::move(cfg));
    std::cout << "Тест создания конфигураций датчика освещения" << "\n";
    LightConfig lcfg;
    const std::filesystem::path path = "../config/LightConfig.json";
    lcfg.fromJson(path);
    lcfg.print();


    
    std::cout << "BYE === SCADA === \n";
    return 0;
}
