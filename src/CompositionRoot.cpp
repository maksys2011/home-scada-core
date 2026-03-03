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

CompositionRoot::CompositionRoot(const ConfigLoader &cfg) 
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

void CompositionRoot::initSensors(AppConfig &&cfg)
{
    initArchive();
    initLogger();
    initClinets(std::move(cfg));
    initSources(std::move(cfg));
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

void CompositionRoot::initActuators(AppConfig &&cfg)
{
}

void CompositionRoot::initClinets(AppConfig &&configs)
{
    for(const auto& config : configs.modbusClientConfig_){
        clientById_.emplace(config.getClientId(),
        std::make_unique<ModbusClient>(config)
        );
    }
}

void CompositionRoot::initSources(AppConfig &&configs)
{
    if(clientById_.empty()){
        throw std::runtime_error("No TCP clients available");
    }

    for(const auto& config : configs.modbusSourceConfigs_){

        auto idClient = config.getClientId();
        auto it = clientById_.find(idClient);

        if(it == clientById_.end()){
            throw std::runtime_error("No TCP clients available");
        }

        sourceById_.emplace(config.getSourceId(),
        std::make_unique<ModbusSource>(config, *(it->second)));
    }
}

void CompositionRoot::printSensors()
{
    for(const auto& sensor : sensorById_){
        sensor.second->print();
    }
   
}

void CompositionRoot::printClients()
{
    for(const auto& client : clientById_){
        client.second->print();
    }
}

void CompositionRoot::printSources()
{
    for(const auto& source : sourceById_){
        source.second->print();
        std::cout << std::endl;
    }
}
