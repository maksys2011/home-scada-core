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

    std::string addr = "tcp://localhost:1883";
    std::string id = "home-scada-client";
    std::vector<std::string> topics{
        "home/kitchen/sensor/humidity",
        "home/living_room/sensor/humidity",
        "home/bedroom/sensor/humidity"
    };

    MqttClient client(addr ,id);
    client.connect(topics);
    MqttWorker worker(client);
    worker.start();
    std::this_thread::sleep_for(std::chrono::seconds(2));

    for(int i = 0; i < 10; i++){
        for(auto topic : topics){

           auto value = worker.getDataPoints(topic);

           if(value){
            std::cout << "value: " << (*value).value << std::endl;
           }else{
            std::cout << "value: " << 0.0 << std::endl;
           }
           std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        std::this_thread::sleep_for(std::chrono::seconds(2));

    }


    




    return 0;
}
