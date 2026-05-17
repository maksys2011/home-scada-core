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

    std::filesystem::path path = "../configs/clients/plcClient.json";
    ModbusClientConfig config;
    config.fromJson(path);
    ModbusClient client(config);
    client.connect();
    for(int i = 0; i < 10; i++){
       uint16_t value = client.readHolding(1); 
       std::cout << "value= " << value << std::endl;
       std::this_thread::sleep_for(std::chrono::seconds(5));
    }
    






    /*
    std::cout << "[Main] thread id = " 
          << std::this_thread::get_id() 
          << std::endl;
          
    AppConfig configs;
    ConfigLoader loader;
    configs = loader.load();
    CompositionRoot root(loader);
    root.init(configs);
    Application app(configs,loader,root);
    app.run();
    */
    return 0;
}
