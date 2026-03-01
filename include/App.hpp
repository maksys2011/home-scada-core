#pragma once
#include <memory>

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


class App
{
public:
    App();
    void run(AppConfig&& cfg);
    bool repl(std::string& line);
    void printAllActuators() const;
    void printActuatorStatus(const std::string& id)const;
    void turnOnActruator(const std::string& id);
    void turnOffActuator(const std::string& id);
    void listActurator()const;

private:
    void init(AppConfig&& cfg);
    void init2(AppConfig&& configs);
    void tick();
    void shutdown();
    
    bool running_ = true;
    std::unique_ptr<Logger>                 logger_;
    std::unique_ptr<Archive>                archive_;
    std::unique_ptr<Sensor>                 sensor_;
    std::unique_ptr<Actuator>               actuator_;
    std::unique_ptr<RuleEngine>             engine_; 
    std::unique_ptr<RuleThermostat>         thermoRule_;
    std::unique_ptr<RandomSource>           source2_;
    std::unique_ptr<RandomSource>           source3_;
    std::unique_ptr<SmoothRandomSource>     source4_;
    std::unique_ptr<ModbusSource>           source5_;
    std::unique_ptr<RuleThermostatConfig >  ruleConfig_;
    std::unique_ptr<ModbusClient>           client_;

    RuleThermostatConfig ruleCfg_;
    ConfigLoader cfg_;

    std::unordered_map<std::string, std::unique_ptr<Actuator>> actuatorById_;
    std::unordered_map<std::string, std::unique_ptr<Sensor>> sensorById_;
    std::unordered_map<std::string, std::unique_ptr<RuleConfig>> ruleConfigById_;
    std::unordered_map<std::string, std::unique_ptr<ModbusClient>> modbusClients_;
    std::unordered_map<std::string, std::unique_ptr<ModbusSource>> modbusSources_;
};