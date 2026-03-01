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
#include "ModbusSource.hpp"
#include "ModbusSourceConfig.hpp"
#include "ModbusClient.hpp"
#include "ModbusClientConfig.hpp"

int main() { 
    
    ModbusClientConfig cfgClient;
    std::filesystem::path path = "../clientConfig/plcClientConfig.json";
    cfgClient.fromJson(path);
    cfgClient.print();

    std::cout << std::endl;

    std::filesystem::path path1 = "../sourceConfig/SourceConfigCoil.json";
    ModbusSourceConfig cfgModbusSource;
    cfgModbusSource.fromJson(path1);
    cfgModbusSource.print();
    

    return 0;
}

