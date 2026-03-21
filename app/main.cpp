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

int main() 
{    
    std::filesystem::path path = "../sourceConfig/SourceConfigMqtt.json";
    MqttSourceConfig config;
    config.fromJson(path);

    MqttSource source(config);

    if(!source.connect()){
        std::cerr << "MQTT connect failed" << '\n';
        return 1;
    }
    while(true){
        std::cout << "MQTT value= " << source.readValue() << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    /*
    ConfigLoader cfg;
    AppConfig apConfig = cfg.load();
    CompositionRoot composit(cfg);
    Application app(apConfig, cfg, composit);
    app.run();
    */
    std::cout << "hello world" << std::endl;


    return 0;
}





 




