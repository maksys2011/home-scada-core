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

int main() { 

    std::cout << "Hello === SCADA === \n";
    std::string ip = "127.0.0.0";
    int port = 1503;
    int slaveId = 1;
    ModbusSourceConfig configModbus;
    ModbusSourceConfig configModnus2;
    std::filesystem::path path = "../sourceConfig/SourceConfigCoil.json";
    std::filesystem::path path2 = "../sourceConfig/SourceConfigCoil2.json";
    configModbus.fromJson(path);
    configModnus2.fromJson(path2);
    ModbusClient client(ip, port, slaveId);
    ModbusSource source(configModbus, client);
    ModbusSource source2(configModnus2, client);
    client.connect();
    for(int i = 0; i < 10; i++){
        std::cout << "value temperature= " << source.readValue() << std::endl;
        std::cout << "value light= " << source2.readValue() << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    
    /*
    App ap;
    AppConfig cfg;
    ap.run(std::move(cfg));
    std::cout << "\n";
    ConfigLoader configPrice;
    configPrice.load();
    */
    std::cout << "BYE === SCADA === \n";
    
    return 0;
}
