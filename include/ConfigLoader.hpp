#pragma once
#include <string>
#include <vector>
#include <filesystem>
#include <nlohmann/json.hpp>

#include "SensorConfig.hpp"

using json = nlohmann::json;

class ActuatorConfig;
class RuleConfig;

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
    ConfigLoader(const AppPath& paths);
    std::vector<SensorConfig> loadSensors();
    std::vector<ActuatorConfig> loadActuators();
    std::vector<RuleConfig> loadRules();

private:
    AppPath paths_;

    
};