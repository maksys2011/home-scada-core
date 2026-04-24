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
using json = nlohmann::json;

int main()
{

    // test PLCWorker

    ModbusClientConfig config("100", "PlC_owen", "0.0.0.0", 1503, 1);

    ModbusClient client(config);

    std::vector<ModbusReadPoint> reg;

    std::filesystem::path path = "../configs/sources/sourceT.json";

    std::ifstream file = scada::utils::create_json_ifstream(path);

    json j;
    file >> j;

    for (const auto& item : j)
    {
        ModbusReadPoint data;
        data.key = item.at("source_id").get<std::string>();
        data.count = 1;
        data.regType = ParseModbusRegisterType(item.at("register_type").get<std::string>());
        data.slaveId = item.at("slave_id").get<int>();
        data.startAddress = item.at("startAddress").get<int>();
        reg.push_back(data);
    }

    PlcWorker worker(client, reg);

    worker.start();

    std::this_thread::sleep_for(std::chrono::seconds(1));

    for (const auto& it : reg)
    {
        std::string key = it.key;
        auto result = worker.getDataPoint(key);
        if (result == std::nullopt)
            continue;
        else
        {
            std::cout << it.key << " = " << result->value << std::endl;
        }
    }

    worker.stop();
    
    return 0;
}
