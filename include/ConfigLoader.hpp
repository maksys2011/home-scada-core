#pragma once
#include <string>
#include <vector>
#include <filesystem>
#include <nlohmann/json.hpp>
#include <memory>
#include "SensorConfig.hpp"
#include "ActuatorConfig.hpp"
#include "RuleConfig.hpp"
#include "RuleThermostatConfig.hpp"
#include "RuleConfigLight.hpp"
#include "ModbusSourceConfig.hpp"
#include "ModbusClientConfig.hpp"
#include "MqttSourceConfig.hpp"
#include "Source.hpp"
#include "SourceConfig.hpp"
#include "BaseActuatorConfig.hpp"
#include "ModbusActuatorConfig.hpp"
#include "MqttActuatorConfig.hpp"
using json = nlohmann::json;

struct AppPath
{
    std::filesystem::path fileCfgSensorPath;
    std::filesystem::path fileCfgActuator;
    std::filesystem::path fileCfgRuleLight;
    std::filesystem::path fileCfgRule;
    std::filesystem::path fileLoggerPath;
    std::filesystem::path fileArhivePath; 
    std::filesystem::path fileCfgModbusClient;
    std::filesystem::path fileCfgModbusSource;
    std::filesystem::path fileCfgMqttSource;
    std::filesystem::path fileCfgSource;
    std::filesystem::path fileCfgBaseActuatorConfig;
};

struct AppConfig
{
    std::vector<SensorConfig> sensorConfigs_;
    std::vector<ActuatorConfig> actuatorConfigs_;
    std::vector<ModbusSourceConfig> modbusSourceConfigs_;
    std::vector<std::unique_ptr<RuleConfig>> ruleConfigs_;
    std::vector<ModbusClientConfig> modbusClientConfig_;
    std::vector<MqttSourceConfig> mqttSourceConfig_;
    std::vector<std::unique_ptr<SourceConfig>> sourceConfigs_;
    std::vector<std::shared_ptr<BaseActuatorConfig>> baseActuatorConfig_;
    std::string addr = "tcp://localhost:1883";
    std::string id = "home-scada-client";

    AppConfig() = default;
    AppConfig(AppConfig&&) = default;
    AppConfig& operator=(AppConfig&&) = default;

    AppConfig(const AppConfig&) = delete;
    AppConfig& operator=(const AppConfig&) = delete;
};

class ConfigLoader
{
public:
    ConfigLoader();
    AppConfig load();
    AppPath getPaths() const;

private:
    AppPath paths_;
    std::vector<SensorConfig> loadSensors();
    std::vector<ActuatorConfig> loadActuators();
    std::vector<ModbusSourceConfig>loadSourceModbus();
    std::vector<std::unique_ptr<RuleConfig>> loadRules();
    std::vector<ModbusClientConfig> loadModbusClient();
    std::vector<MqttSourceConfig> loadSourceMqtt();
    std::vector<std::unique_ptr<SourceConfig>> loadSourceConfig();
    std::vector<std::shared_ptr<BaseActuatorConfig>> loadBaseActuatorConfig();
};