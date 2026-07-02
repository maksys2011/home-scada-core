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
#include "ArchiveReader.hpp"
#include "ArchiveReport.hpp"
#include "RuleThermostatConfig.hpp"
#include "RuleEngine.hpp"
#include "RuleThermostat.hpp"
#include "ConfigLoader.hpp"
#include "RuleConfigLight.hpp"
#include "ModbusSource.hpp"
#include "ModbusSourceConfig.hpp"
#include "ModbusClient.hpp"
#include "ModbusClientConfig.hpp"
#include "CompositionRoot.hpp"
#include "Application.hpp"
#include <libpq-fe.h>
#include "PgArchive.hpp"
#include <mqtt/async_client.h>
#include "MqttSourceConfig.hpp"
#include "MqttSource.hpp"
#include "MqttCommandPublisher.hpp"
#include "GenericActuator.hpp"
#include "PlcWorker.hpp"
#include "MqttClient.hpp"
#include "MqttWorker.hpp"
#include "ModbusActuatorConfig.hpp"
#include "BaseActuatorConfig.hpp"
using json = nlohmann::json;

int main()
{
    /*
    std::cout << "[Main] thread id = " 
          << std::this_thread::get_id() 
          << std::endl;
          
    AppConfig configs;
    ConfigLoader loader;
    configs = loader.load();
    CompositionRoot root(loader);
    //root.init(configs);
    Application app(configs,loader,root);
    app.run(); */


    json j = {
        {"id_" , "10001"},
        {"name_" , "temperature_kitchen"},
        {"type_" , "Analog"},
        {"unit" , "celsius"},
        {"physicalMin_" , 0.0},
        {"physicalMax_" , 100.0},
        {"noiseEpsilon_" , 0.5},
        {"staleTimeout_" , 500},
        {"warnHigh_" , 50.5},
        {"warnLow_" , 10},
        {"alarmHigh_", 95.0},
        {"alarmLow_", 5.0},
        {"deadband_" , 0.5},
        {"hysteresis_" , 0.2},
        {"enabled_" , false},
        {"source_id" , "500"}};
    
    SensorConfig cfg;
    cfg.fromJson(j);
    SensorState state(cfg);

    std::cout << "value= " << "---" << " state= " << StateToString(state.status()) << std::endl;
    state.processValue(95);
    std::cout << "value= " << 95 << " state= " << StateToString(state.status()) << std::endl;
    state.processValue(96);
    std::cout << "value= " << 96 << " state= " << StateToString(state.status()) << std::endl;
    state.processValue(97);
    std::cout << "value= " << 97 << " state= " << StateToString(state.status()) << std::endl;

    






    return 0;
}
