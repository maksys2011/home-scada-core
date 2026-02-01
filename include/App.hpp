#pragma once
#include <memory>

#include "ConfigLoader.hpp"

class Sensor;
class Actuator;
class RuleEngine;
class Logger;
class Archive;
class testSource;
class RuleThermostat;
class RandomSource;
class RuleConfig;
class RuleThermostatConfig;

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
    void init();
    void tick();
    void shutdown();
    
    bool running_ = true;
    std::unique_ptr<Logger>                 logger_;
    std::unique_ptr<Archive>                archive_;
    std::unique_ptr<Sensor>                 sensor_;
    std::unique_ptr<Actuator>               actuator_;
    std::unique_ptr<RuleEngine>             engine_; 
    std::unique_ptr<testSource>             source_;
    std::unique_ptr<RuleThermostat>         thermoRule_;
    std::unique_ptr<RandomSource>           sourse2_;
    std::unique_ptr<RuleThermostatConfig>   ruleConfig_;
    RuleThermostatConfig ruleCfg_;
    ConfigLoader cfg_;

    std::unordered_map<std::string, std::unique_ptr<Actuator>> actuatorById_;
    std::unordered_map<std::string, std::unique_ptr<Sensor>> sensorById;
    std::unordered_map<std::string, std::unique_ptr<RuleConfig>> ruleConfigById;
};