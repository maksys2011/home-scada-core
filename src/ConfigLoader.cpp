#include "ConfigLoader.hpp"
#include <fstream>
#include <stdexcept>
#include <iostream>
#include "utils.hpp"

ConfigLoader::ConfigLoader()
{
    paths_.fileCfgSensorPath   = "../configs/sensors/sensor.json";
    paths_.fileCfgActuator     = "../configs/actuators/actuator.json";
    paths_.fileCfgRule         = "../configs/rules/rule.json";
    //paths_.fileCfgRuleLight    = "";
    paths_.fileLoggerPath      = "../logs/events.log";
    paths_.fileArhivePath      = "../archive/archive.csv";
    paths_.fileCfgSource       = "../configs/sources/source.json";
    paths_.fileCfgModbusSource = "../configs/sources/SourceConfigModbus.json";
    paths_.fileCfgModbusClient = "../configs/clients/plcClient.json";
    paths_.fileCfgMqttSource   = "../configs/sources/SourceConfigMqtt.json";   
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

std::vector<ModbusClientConfig> ConfigLoader::loadModbusClient()
{
    std::string msg1 = "ModbusClientConfig: cannot open rule config file: ";
    std::string msg2 = "ModbusClientConfig: config must be object or array";
    return scada::factory::loadHierarchy<ModbusClientConfig>(msg1, msg2, paths_.fileCfgModbusClient);
}

std::vector<MqttSourceConfig> ConfigLoader::loadSourceMqtt()
{
    std::string msg1 = "SourceMqttConfig: cannot open config file: ";
    std::string msg2 = "SourceMqttConfig: config must be object or array";
    return scada::factory::loadHierarchy<MqttSourceConfig>(msg1, msg2, paths_.fileCfgMqttSource);
}

std::vector<std::unique_ptr<SourceConfig>> ConfigLoader::loadSourceConfig()
{
    std::string msg1 = "SourceConfig: cannot open config file: ";
    std::string msg2 = "SourceConfig: config must be object or array";
    return scada::source::loadPolymorphic(msg1, msg2, paths_.fileCfgSource);
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
    cfg.modbusClientConfig_  = loadModbusClient();
    cfg.mqttSourceConfig_    = loadSourceMqtt();
    cfg.sourceConfigs_       = loadSourceConfig();
    
    return cfg;
}
