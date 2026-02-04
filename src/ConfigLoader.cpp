#include "ConfigLoader.hpp"
#include <fstream>
#include <stdexcept>
#include <iostream>

ConfigLoader::ConfigLoader()
{
    paths_.fileCfgSensorPath = "../config/SensorConfig.json";
    paths_.fileCfgActuator = "../config/ActuatorConfig.json";
    paths_.fileCfgRule = "../rule/RuleConfigThermostat.json";
    paths_.fileCfgRuleLight = "../rule/RuleConfigLight.json";
    paths_.fileLoggerPath = "../logs/events.log";
    paths_.fileArhivePath = "../archive/archive.csv";
}

std::vector<SensorConfig> ConfigLoader::loadSensors()
{
    std::vector<SensorConfig> result;

    std::ifstream file(paths_.fileCfgSensorPath);
    if(!file.is_open()){
        throw std::runtime_error(
            std::string("SensorConfigLoader: cannot open sensors config file: ")
             + paths_.fileCfgSensorPath.string());
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

std::vector<std::unique_ptr<RuleConfig>> ConfigLoader::loadRules_2()
{
    std::vector<std::unique_ptr<RuleConfig>> result;

    std::ifstream file(paths_.fileCfgRuleLight);
    if(!file.is_open()){
        throw std::runtime_error(
            (std::string)"RuleConfigLoaders: cannot open rule config file"
            +paths_.fileCfgRule.string());
    }

    json j;
    file >> j;

    if(j.is_array()){
        for(const auto& item : j){
                RuleConfigLight cfg;
                cfg.fromJson(item);    
                result.push_back(std::make_unique<RuleConfigLight>(cfg));
        }
    }else if(j.is_object()){
                RuleConfigLight cfg;
                cfg.fromJson(j);
                result.push_back(std::make_unique<RuleConfigLight>(cfg));
    }else{
            throw std::runtime_error(
            (std::string)"RuleConfigLoader: rule config must be object or array");
    }
    
    return result;
}

std::vector<std::unique_ptr<RuleConfig>> ConfigLoader::loadRules_1()
{
    std::vector<std::unique_ptr<RuleConfig>> result;

    std::ifstream file(paths_.fileCfgRule);
    if(!file.is_open()){
        throw std::runtime_error(
            (std::string)"RuleConfigLoaders: cannot open rule config file"
            +paths_.fileCfgRule.string());
    }

    json j;
    file >> j;

    if(j.is_array()){
        for(const auto& item : j){
                RuleThermostatConfig cfg;
                cfg.fromJson(item);
                result.push_back(std::make_unique<RuleThermostatConfig>(cfg));
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

AppPath ConfigLoader::getPaths() const
{
    return paths_;
}



AppConfig ConfigLoader::load()
{
    AppConfig cfg;
    cfg.sensorConfigs_   = loadSensors();
    cfg.actuatorConfigs_ = loadActuators();
    cfg.ruleConfigs_     = loadRules_1();
    cfg.ruleConfigs_2    = loadRules_2();
    
    return cfg;
}
