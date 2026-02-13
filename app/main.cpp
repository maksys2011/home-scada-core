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
using json = nlohmann::json;

int main() { 

    std::cout << "Hello === SCADA === \n";
    
    /*App ap;
    AppConfig cfg;
    ap.run(std::move(cfg));
    std::cout << "\n";
    ConfigLoader configPrice;
    configPrice.load();*/

    std::string ip = "127.0.0.1";
    int port = 1502;
    int startAddress = 0; 

    ModbusSource mSourceTemp(ip, port, 1, startAddress);
    ModbusSource mSourceLight(ip, port, 2, startAddress);

    bool res1 = mSourceTemp.connect();
    bool res2 = mSourceLight.connect();

    for(int i = 0; i < 10; i++){
        double valueTemp = mSourceTemp.readValue();
        double valueLight = mSourceLight.readValue();
        std::cout << "temperature= " << valueTemp << std::endl;
        std::cout << "sensor light= " << valueLight << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    std::cout << "BYE === SCADA === \n";

    return 0;
}
