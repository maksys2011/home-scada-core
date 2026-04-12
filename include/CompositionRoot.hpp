#pragma once
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include "ConfigLoader.hpp"

class Sensor;
class Actuator;
class Logger;
class Archive;
class ModbusClient;
class RuleEngine;
class RuleThermostat;
class RuleThermostatConfig;
class RuleControlLight;
class RuleConfigLight;
class RuleConfig;
class testSource;
class RandomSource;
class SmoothRandomSource;
class ModbusSource;
class Source;
class Rule;
class PgArchive;
class IActuator;
class MqttCommandPublisher;
class ITransport;

class CompositionRoot
{
public:
    CompositionRoot() = default;
    CompositionRoot(const ConfigLoader& cfg);
    ~CompositionRoot();
        
    void initLogger();
    void initArchive();
    void initPgArchive();
    void initSensors(const AppConfig& cfg);
    void initActuators(const AppConfig& cfg);
    void initClients(const AppConfig& cfg);
    void initSources(const AppConfig& cfg);
    void initRules(const AppConfig& cfg);

    void initModbusClient(const AppConfig& cfg);
    void initMqttCommandPublisher(const AppConfig& cfg);
    void initIactuators(const AppConfig& cfg);

    void init(const AppConfig& cfg);

    const std::vector<std::unique_ptr<Rule>>& getRuleById() const { return ruleById_; };
    const std::unordered_map<std::string, std::unique_ptr<Sensor>>& getSensorById() const { return sensorById_; };
    const std::unique_ptr<RuleEngine>& getRuleEngine() const { return engine_; };
    const std::unordered_map<std::string, std::unique_ptr<Actuator>>& getActuatorById() const { return actuatorById_; };
    const std::unordered_map<std::string, std::unique_ptr<IActuator>>& getIActuatorById() const { return iActuatorById_; };
    
    void printSensors() const;
    void printClients() const;
    void printSources() const;
    void printActuator() const;
    void printRule() const;

private:
    AppConfig configList_;
    ConfigLoader configs_;
    std::unique_ptr<RuleEngine> engine_;
    std::unique_ptr<Logger> logger_;
    std::unique_ptr<Archive> archive_;
    std::unique_ptr<PgArchive> pgArchive_;
    std::unordered_map<std::string, std::unique_ptr<Sensor>> sensorById_;
    std::unordered_map<std::string, std::unique_ptr<Actuator>> actuatorById_;
    std::unordered_map<std::string, std::unique_ptr<ModbusClient>> clientById_;
    std::unordered_map<std::string, std::unique_ptr<Source>> sourceById_;
    std::vector<std::unique_ptr<Rule>> ruleById_;

    std::unordered_map<std::string, std::shared_ptr<ModbusClient>> modbusClientById_;
    std::unordered_map<std::string, std::shared_ptr<MqttCommandPublisher>> mqttCommandPublisherById_;
    std::unordered_map<std::string, std::shared_ptr<ITransport>> transportById_;
    std::unordered_map<std::string, std::unique_ptr<IActuator>> iActuatorById_;

};