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
class PlcWorker;
struct ModbusReadPoint;
class MqttClient;
class MqttWorker;
class QtGuiSubscriber;
class Dispatcher;

class CompositionRoot
{
public:
    CompositionRoot() = delete;
    CompositionRoot(const ConfigLoader& cfg);
    ~CompositionRoot();
        
    void initLogger();
    void initArchive();
    void initPgArchive();
    void initSubscriber();
    void initDispatcher();

    void addSubscriber();

    void initSensors(const AppConfig& cfg);
    void initActuators(const AppConfig& cfg);
    void initClients(const AppConfig& cfg);
    void initPlcWorker(const AppConfig& cfg);
    void initSources(const AppConfig& cfg);
    void initRules(const AppConfig& cfg);

    void initModbusClient(const AppConfig& cfg);
    void initMqttCommandPublisher(const AppConfig& cfg);
    void initIactuators(const AppConfig& cfg);

    void initMqttClient(const AppConfig& cfg);
    void initMqttWorker();

    void init(const AppConfig& cfg);

    const std::vector<std::unique_ptr<Rule>>& getRuleById() const { 
        return ruleById_; };
    
    const std::unordered_map<std::string, std::unique_ptr<Sensor>>& getSensorById() const {
        return sensorById_; };
    
    const std::unique_ptr<RuleEngine>& getRuleEngine() const { 
        return engine_; };
    
    const std::unordered_map<std::string, std::unique_ptr<Actuator>>& getActuatorById() const { 
        return actuatorById_; };
    
    const std::unordered_map<std::string, std::unique_ptr<IActuator>>& getIActuatorById() const {
        return iActuatorById_; };
    
    const std::unordered_map<std::string, std::unique_ptr<PlcWorker>>& getPlcWorkerById() const {
        return plcWorkerById_; };
    
    const std::unordered_map<std::string, std::unique_ptr<Source>>& getSourceById() const {
        return sourceById_; };
    
    const std::unique_ptr<RuleEngine>& getEngine() { return engine_; };

    const std::unordered_map<std::string, std::shared_ptr<ModbusClient>>& getClientModbus() const {
        return modbusClientById_;
    };

    const std::unordered_map<std::string, std::unique_ptr<ModbusClient>>& getClient() const {
        return clientById_;
    };

    std::unique_ptr<MqttWorker>& getMqttWorker() { return mqtt_worker_; };
    
    std::unique_ptr<MqttClient>& getClientMqtt() { return mqtt_client_; };
    
    std::vector<std::string> getMqttCollectionTopics() const {return mqtt_collection_topics_; };

    std::unique_ptr<Dispatcher>& getDispatsher() { return dispatcher_; };

    void printSensors() const;
    void printClients() const;
    void printSources() const;
    void printActuator() const;
    void printRule() const;

private:
    AppConfig configList_;
    ConfigLoader configs_;
    
    std::unique_ptr<MqttClient> mqtt_client_;
    std::unique_ptr<MqttWorker> mqtt_worker_;
    std::vector<std::string> mqtt_collection_topics_;
    
    std::unique_ptr<RuleEngine> engine_;
    
    std::unique_ptr<Logger> logger_;
    std::unique_ptr<Archive> archive_;
    std::unique_ptr<PgArchive> pgArchive_;
    std::unique_ptr<QtGuiSubscriber> qtSubscriber_;

    std::unique_ptr<Dispatcher> dispatcher_; 

    std::unordered_map<std::string, std::unique_ptr<Sensor>> sensorById_;
    std::unordered_map<std::string, std::unique_ptr<Actuator>> actuatorById_;
    std::unordered_map<std::string, std::unique_ptr<ModbusClient>> clientById_;
    std::unordered_map<std::string, std::unique_ptr<Source>> sourceById_;
    std::vector<std::unique_ptr<Rule>> ruleById_;
    std::unordered_map<std::string, std::shared_ptr<ModbusClient>> modbusClientById_;
    std::unordered_map<std::string, std::shared_ptr<MqttCommandPublisher>> mqttCommandPublisherById_;
    std::unordered_map<std::string, std::shared_ptr<ITransport>> transportById_;
    std::unordered_map<std::string, std::unique_ptr<IActuator>> iActuatorById_;
    std::unordered_map<std::string, std::unique_ptr<PlcWorker>> plcWorkerById_;
    std::unordered_map<std::string, std::vector<ModbusReadPoint>> list_of_registers_;
};