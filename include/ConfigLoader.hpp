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

using json = nlohmann::json;

struct AppPath
{
    std::filesystem::path fileCfgSensorPath;
    std::filesystem::path fileCfgActuator;
    std::filesystem::path fileCfgRuleLight;
    std::filesystem::path fileCfgRule;
    std::filesystem::path fileLoggerPath;
    std::filesystem::path fileArhivePath; 
};

struct AppConfig
{
    std::vector<SensorConfig>                sensorConfigs_;
    std::vector<ActuatorConfig>              actuatorConfigs_;
    std::vector<std::unique_ptr<RuleConfig>> ruleConfigs_;
    std::vector<std::unique_ptr<RuleConfig>> ruleConfigs_2;

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
    std::vector<std::unique_ptr<RuleConfig>> loadRules_1();
    std::vector<std::unique_ptr<RuleConfig>> loadRules_2();
};