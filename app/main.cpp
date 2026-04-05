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

    ConfigLoader loadConfigs;
    AppConfig a = loadConfigs.load();
    for(const auto& it : a.sourceConfigs_){
        it->print();
        std::cout << std::endl;
    }
    
    
    


    return 0;
}





 




