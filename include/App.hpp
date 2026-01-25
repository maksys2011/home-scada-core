#pragma once
#include <memory>
#include "RuleThermostatConfig.hpp"

class Sensor;
class Actuator;
class RuleEngine;
class Logger;
class Archive;
class testSource;
class RuleThermostat;

class App
{
public:
    App();
    void run();
    bool repl(std::string& line);

    private:
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
    RuleThermostatConfig ruleCfg_;
    std::unordered_map<std::string, Actuator*> actuatorById_;
};