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
using json = nlohmann::json;

int main()
{

    /*
    std::cout << "[Main] thread id = " 
          << std::this_thread::get_id() 
          << std::endl;
          
    AppConfig config;
    ConfigLoader loader;
    config = loader.load();
    CompositionRoot root(loader);
    Application scada(config, loader, root);
    scada.run();*/

    std::string addr = "home-scada-client";
    std::string id = "tcp://localhost:1883";
    std::vector<std::string> topics{
        "home/bedroom2/sensor/light"
    };

    MqttClient client(addr ,id);
    client.connect(topics);
    




    return 0;
}
