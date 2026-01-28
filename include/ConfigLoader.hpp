#pragma once

#include <string>
#include <vector>
#include <filesystem>
#include <nlohmann/json.hpp>
#include <memory>

#include "SensorConfig.hpp"
#include "ActuatorConfig.hpp"
#include "RuleConfig.hpp"

using json = nlohmann::json;

struct AppPath
{
    std::filesystem::path fileSensorConfigPath;
    std::filesystem::path fileLoggerPath;
    std::filesystem::path fileArchivePath;
    std::filesystem::path fileCfgActuator;
    std::filesystem::path fileCfgRuleThermostat;
};

class ConfigLoader
{
public:
    ConfigLoader();
    std::vector<SensorConfig> loadSensors();
    std::vector<ActuatorConfig> loadActuators();
    std::vector<std::unique_ptr<RuleConfig>> loadRules();

private:
    AppPath paths_;

    
};