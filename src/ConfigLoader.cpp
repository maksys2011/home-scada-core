#include "ConfigLoader.hpp"
#include <fstream>
#include <stdexcept>

ConfigLoader::ConfigLoader()
{
    paths_.fileSensorConfigPath = "../config/SensorConfig.json";
    paths_.fileCfgActuator = "../config/ActuatorConfig.json";
    paths_.fileRuleConfig = "../rule/ruleConfigThermostat.json";
}

std::vector<SensorConfig> ConfigLoader::loadSensors()
{
    std::vector<SensorConfig> result;

    std::ifstream file(paths_.fileSensorConfigPath);
    if(!file.is_open()){
        throw std::runtime_error(
            std::string("SensorConfigLoader: cannot open sensors config file: ")
             + paths_.fileSensorConfigPath.string());
    }

    json j;
    file >> j;

    if(j.is_array()){
        for(const auto& item : j){
            SensorConfig cfg;
            cfg.fromJson(item);
            result.push_back(cfg);
        }
    }else if(j.is_object()){
        SensorConfig cfg;
        cfg.fromJson(j);
        result.push_back(cfg);
    }else{
        throw std::runtime_error(
            "SensorConfigLoader: sensors config must be object or array"
        );
    }

    return result;
}

std::vector<ActuatorConfig> ConfigLoader::loadActuators()
{
    std::vector<ActuatorConfig> result;

    std::ifstream file(paths_.fileCfgActuator);

    if(!file.is_open()){
        throw std::runtime_error(
            std::string("ActuatorConfigLoader: cannot open actuator config file")
            + paths_.fileCfgActuator.string());
    }

    json j;
    file >> j;

    if(j.is_array()){
        for(const auto& item : j){
            ActuatorConfig actCfg;
            actCfg.fromJson(item);
            result.push_back(actCfg);
        }
    }else if(j.is_object()){
        ActuatorConfig actCfg;
        actCfg.fromJson(j);
        result.push_back(actCfg);
    }else{
        throw std::runtime_error(
            "ActuatorConfigLoader: actuator config must be object or array"
        );
    }

    return result;
}

std::vector<std::unique_ptr<RuleConfig>> ConfigLoader::loadRules()
{
    std::vector<std::unique_ptr<RuleConfig>> result;

    std::ifstream file(paths_.fileRuleConfig);
    if(!file.is_open()){
        throw std::runtime_error(
            (std::string)"RuleConfigLoaders: cannot open rule config file"
            +paths_.fileRuleConfig.string());
    }

    json j;
    file >> j;

    if(j.is_array()){
        for(const auto& item : j){
            if("Thermostat" == item.at("name").get<std::string>()){
            RuleThermostatConfig cfg;
            cfg.fromJson(item);
            result.push_back(std::make_unique<RuleThermostatConfig>(cfg));
            }
        }
    }else if(j.is_object()){
        RuleThermostatConfig cfg;
        cfg.fromJson(j);
        result.push_back(std::make_unique<RuleThermostatConfig>(cfg));
    }else{
        throw std::runtime_error(
            (std::string)"RuleConfigLoader: rule config must be object or array");
    }

    return result;
}
