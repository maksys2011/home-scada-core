#include "ConfigLoader.hpp"
#include <fstream>
#include <stdexcept>
#include <iostream>
#include "utils.hpp"

ConfigLoader::ConfigLoader()
{
    paths_.fileCfgSensorPath = "../config/SensorConfig.json";
    paths_.fileCfgActuator = "../config/ActuatorConfig.json";
    paths_.fileCfgRule = "../ruleConfig/RuleConfigThermostat.json";
    paths_.fileCfgRuleLight = "../ruleConfig/RuleConfigLight.json";
    paths_.fileLoggerPath = "../logs/events.log";
    paths_.fileArhivePath = "../archive/archive.csv";
    paths_.fileCfgModbusSource = "../sourceConfig/SourceConfigCoil.json";
}

std::vector<SensorConfig> ConfigLoader::loadSensors()
{
    std::string msg1 = "SensorConfigLoader: cannot open sensors config file: ";
    std::string msg2 = "SensorConfigLoader: sensors config must be object or array";
    return scada::factory::loadHierarchy<SensorConfig>(msg1, msg2, paths_.fileCfgSensorPath);
}

std::vector<ActuatorConfig> ConfigLoader::loadActuators()
{
    std::string msg1 = "ActuatorConfigLoader: cannot open actuator config file: ";
    std::string msg2 = "ActuatorConfigLoader: actuator config must be object or array";
    return scada::factory::loadHierarchy<ActuatorConfig>(msg1, msg2, paths_.fileCfgActuator);
}

std::vector<ModbusSourceConfig> ConfigLoader::loadSourceModbus()
{
    std::string msg1 = "ModbusSourceConfig: cannot open config file: ";
    std::string msg2 = "ModbusSourceConfig: config must be object or array";
    return scada::factory::loadHierarchy<ModbusSourceConfig>(msg1, msg2, paths_.fileCfgModbusSource);
}


std::vector<std::unique_ptr<RuleConfig>> ConfigLoader::loadRules()
{
    std::string msg1 = "RuleConfigLoaders: cannot open rule config file: ";
    std::string msg2 = "RuleConfigLoader: rule config must be object or array";
    return scada::factory::loadPolymorphic(msg1, msg2, paths_.fileCfgRule);
}

AppPath ConfigLoader::getPaths() const
{
    return paths_;
}

AppConfig ConfigLoader::load()
{
    AppConfig cfg;
    cfg.sensorConfigs_       = loadSensors();
    cfg.actuatorConfigs_     = loadActuators();
    cfg.modbusSourceConfigs_ = loadSourceModbus();
    cfg.ruleConfigs_         = loadRules();
    
    return cfg;
}
