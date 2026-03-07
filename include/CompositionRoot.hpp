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


class CompositionRoot
{
public:
    CompositionRoot() = default;
    CompositionRoot(const ConfigLoader& cfg);
    
    void initLogger();
    void initArchive();
    void initSensors(const AppConfig& cfg);
    void initActuators(const AppConfig& cfg);
    void initClients(const AppConfig& cfg);
    void initSources(const AppConfig& cfg);
    void initRules(const AppConfig& cfg);
    void init(const AppConfig& cfg);

    const std::vector<std::unique_ptr<Rule>>& getRuleById() const { return ruleById_; };
    const std::unordered_map<std::string, std::unique_ptr<Sensor>>& getSensorById() const { return sensorById_; };
    const std::unique_ptr<RuleEngine>& getRuleEngine() const { return engine_; };
    
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
    std::unordered_map<std::string, std::unique_ptr<Sensor>> sensorById_;
    std::unordered_map<std::string, std::unique_ptr<Actuator>> actuatorById_;
    std::unordered_map<std::string, std::unique_ptr<ModbusClient>> clientById_;
    std::unordered_map<std::string, std::unique_ptr<Source>> sourceById_;
    std::vector<std::unique_ptr<Rule>> ruleById_;
};