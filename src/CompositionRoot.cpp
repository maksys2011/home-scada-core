#include "CompositionRoot.hpp"
#include "RandomSource.hpp"
#include "Sensor.hpp"
#include "Actuator.hpp"
#include "Logger.hpp"
#include "Archive.hpp"
#include "ModbusClient.hpp"
#include "ModbusSource.hpp"
#include "ModbusSourceConfig.hpp"
#include "Source.hpp"
#include "Rule.hpp"
#include "RuleThermostat.hpp"
#include "RuleControlLight.hpp"

CompositionRoot::CompositionRoot(const ConfigLoader& cfg) 
    : configs_(cfg)
{}

void CompositionRoot::initLogger()
{
    const auto& path = configs_.getPaths().fileLoggerPath;
    logger_ = std::make_unique<Logger>(path);
}

void CompositionRoot::initArchive()
{
    const auto& path = configs_.getPaths().fileArhivePath;
    archive_ = std::make_unique<Archive>(path);
}

void CompositionRoot::initSensors(const AppConfig& cfg)
{
    initArchive();
    initLogger();
    initClients(cfg);
    initSources(cfg);
    if(!logger_){
        throw std::runtime_error("logger is not initialized");
    }
    if(!archive_){
        throw std::runtime_error("archive is not initialized");
    }

    for(const auto& configSensor : cfg.sensorConfigs_){
        auto source = sourceById_.find(configSensor.getSourceId());
        if(source == sourceById_.end()){
            throw std::runtime_error("No suitable data source found");
        }
        sensorById_.emplace(
            configSensor.getId(),
            std::make_unique<Sensor>(
                configSensor,
                logger_.get(),
                archive_.get(),
                source->second.get()
            )
        );
    }
}

void CompositionRoot::initActuators(const AppConfig& cfg)
{
    for(const auto& config : cfg.actuatorConfigs_){
        actuatorById_.emplace(config.getId(),
        std::make_unique<Actuator>(config)
    );
    }
}

void CompositionRoot::initClients(const AppConfig& cfg)
{
    for(const auto& config : cfg.modbusClientConfig_){
        clientById_.emplace(config.getClientId(),
        std::make_unique<ModbusClient>(config)
        );
    }
}

void CompositionRoot::initSources(const AppConfig& cfg)
{
    if(clientById_.empty()){
        throw std::runtime_error("No TCP clients available");
    }

    for(const auto& config : cfg.modbusSourceConfigs_){

        auto idClient = config.getClientId();
        auto it = clientById_.find(idClient);

        if(it == clientById_.end()){
            throw std::runtime_error("No TCP clients available");
        }

        sourceById_.emplace(config.getSourceId(),
        std::make_unique<ModbusSource>(config, *(it->second)));
    }
}

void CompositionRoot::initRules(const AppConfig &cfg)
{
    for(const auto& config : cfg.ruleConfigs_){
        const RuleType type = config->getRuleType();
        const auto& sensor = sensorById_.find(config->getSensorId());
        const auto& actuator = actuatorById_.find(config->getActuatorId());
        auto& state = sensor->second->state();
        
        switch (type)
        {
        case RuleType::Thermostat:{
            
            const auto& thermostatConfig = static_cast<const RuleThermostatConfig&>(*config);
           
            ruleById_.push_back(
                std::make_unique<RuleThermostat>(state, *(actuator->second), thermostatConfig));
                break;
            }
        case RuleType::Light:{

            const auto& lightConfig = static_cast<const RuleConfigLight&>(*config);
            
            ruleById_.push_back(
                std::make_unique<RuleControlLight>(state, *(actuator->second), lightConfig));
                break;
            }
        }

    }
}

void CompositionRoot::init(const AppConfig& cfg)
{
    initLogger();
    initArchive();
    initSensors(cfg);
    initClients(cfg);
    initSources(cfg);
    initActuators(cfg);
    initRules(cfg);
}

void CompositionRoot::printSensors() const
{
    for(const auto& sensor : sensorById_){
        sensor.second->print();
    }
   
}

void CompositionRoot::printClients() const 
{
    for(const auto& client : clientById_){
        client.second->print();
    }
}

void CompositionRoot::printSources() const 
{
    for(const auto& source : sourceById_){
        source.second->print();
        std::cout << std::endl;
    }
}

void CompositionRoot::printActuator() const
{
    for(const auto& actuator : actuatorById_){
        actuator.second->print();
    }
}

void CompositionRoot::printRule() const
{
    std::cout << "Rule: " << ruleById_.size() << std::endl;
}
