#include "ConfigLoader.hpp"
#include <fstream>

ConfigLoader::ConfigLoader(const AppPath &paths) : paths_(paths){}

std::vector<SensorConfig> ConfigLoader::loadSensors()
{
    std::vector<SensorConfig> result;

    std::ifstream file(paths_.fileSensorConfigPath);
    if(!file.is_open()){
        throw std::runtime_error(
            "ConfigLoader: cannot open sensors config file: " +
                paths_.fileSensorConfigPath.string()
        );
    }

    json j;
    file >> j;

    if(j.is_array()){
        for(const auto& item : j){
            SensorConfig cfg;
            cfg.fromJson(item);
            result.push_back(cfg);
        }
    }else if(j.object()){
        SensorConfig cfg;
        cfg.fromJson(j);
        result.push_back(cfg);
    }else{
        throw std::runtime_error(
            "ConfigLoader: sensors config must be object or array"
        );
    }

    return result;
}

std::vector<ActuatorConfig> ConfigLoader::loadActuators()
{
    return std::vector<ActuatorConfig>();
}

std::vector<RuleConfig> ConfigLoader::loadRules()
{
    return std::vector<RuleConfig>();
}
