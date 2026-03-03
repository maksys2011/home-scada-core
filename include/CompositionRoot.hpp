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


class CompositionRoot
{
public:
    CompositionRoot() = default;
    CompositionRoot(const ConfigLoader& cfg);
    void initLogger();
    void initArchive();
    void initSensors(AppConfig&& configs);
    void initActuators(AppConfig&& configs);
    void initClinets(AppConfig&& configs);
    void initSources(AppConfig&& configs);

    void printSensors();
    void printClients();
    void printSources();



private:
    ConfigLoader configs_;
    std::unique_ptr<Logger> logger_;
    std::unique_ptr<Archive> archive_;
    std::unordered_map<std::string, std::unique_ptr<Sensor>> sensorById_;
    std::unordered_map<std::string, std::unique_ptr<Actuator>> actuatorById_;
    std::unordered_map<std::string, std::unique_ptr<ModbusClient>> clientById_;
    std::unordered_map<std::string, std::unique_ptr<Source>> sourceById_;
};