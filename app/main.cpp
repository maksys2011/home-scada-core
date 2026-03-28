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

int main() 
{    
    /*
    SensorConfig config;
    std::filesystem::path path = "../config/SensorConfigTemperatureMqtt.json";
    std::filesystem::path pathLog = "../logs/events.log";
    std::filesystem::path pathArch = "../archive/archive.csv";
    std::filesystem::path pathSource = "../sourceConfig/SourceConfigMqtt.json";
    config.fromJson(path);
    config.print();
    Logger lg(pathLog);
    Archive arch(pathArch);
    MqttSourceConfig configSource;
    configSource.fromJson(pathSource);
    MqttSource source(configSource);
    source.connect();
    PgArchive pgArchive("dbname=homescada user=maksys2011");
    Sensor sensor(config, &lg, &arch, pgArchive, &source);
    for(int i = 0; i < 10; i++){
        sensor.update();
        sensor.state().processValue(source.readValue());
        double value = *sensor.state().lastValue();
        std::cout << value << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }
    
    /*
    ConfigLoader cfg;
    AppConfig apConfig = cfg.load();
    CompositionRoot composit(cfg);
    Application app(apConfig, cfg, composit);
    app.run();
    */
    std::string broker = "tcp://localhost:1883";
    std::string topic = "home/test/cmd";
    std::string client = "home-scada-client";
    MqttCommandPublisher cmd(broker, client);
    cmd.connect();
    
    for(size_t i = 0; i < 10; i++){
        cmd.publishOn(topic);
        std::this_thread::sleep_for(std::chrono::seconds(5));
        cmd.publishOff(topic);
    }

    
    return 0;
}





 




