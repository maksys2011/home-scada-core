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
#include "RuleEngine.hpp"
#include "PgArchive.hpp"
#include "ModbusTransport.hpp"
#include "MqttTransport.hpp"
#include "IActuator.hpp"
#include "ITransport.hpp"
#include "GenericActuator.hpp"
#include "MqttClient.hpp"
#include "MqttWorker.hpp"
#include "MqttSource.hpp"

CompositionRoot::CompositionRoot(const ConfigLoader& cfg) 
    : configs_(cfg)
{
    engine_ = std::make_unique<RuleEngine>();
}

CompositionRoot::~CompositionRoot() = default;

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

void CompositionRoot::initPgArchive()
{
    const std::string connInfo = "dbname=homescada user=maksys2011";
    pgArchive_ = std::make_unique<PgArchive>(connInfo);
}

void CompositionRoot::initSensors(const AppConfig& cfg)
{
    if(!logger_){
        throw std::runtime_error("logger is not initialized");
    }

    if(!archive_){
        throw std::runtime_error("archive is not initialized");
    }

    if(!pgArchive_){
        throw std::runtime_error("pgArchive is not initialized");
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
                *pgArchive_,
                source->second.get()
            )
        );
    }
}

void CompositionRoot::initActuators(const AppConfig& cfg)
{
    if(clientById_.empty()){
        throw std::runtime_error("No TCP clients available");
    }

    for(const auto& config : cfg.actuatorConfigs_){
        auto idClient = config.getIdClient();
        auto it = clientById_.find(idClient);

        if(it == clientById_.end()){
            throw std::runtime_error("No TCP clients available");
        }
        
        actuatorById_.emplace(config.getId(),
        std::make_unique<Actuator>(config,  *(it->second))
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

void CompositionRoot::initPlcWorker(const AppConfig& cfg)
{
    if(clientById_.empty()){
        throw std::runtime_error(
            "No TCP clients available"
        );
    }

    for(const auto& config : cfg.sourceConfigs_){
        if(config->getTypeSource() == "Modbus"){

            auto modbus_source_config = dynamic_cast<ModbusSourceConfig*>(config.get());

            if(!modbus_source_config){
                throw std::runtime_error
                ("SourceConfig type mismatch:expected ModbusSourceConfig for source type Modbus");
            }

            ModbusReadPoint reg;
            reg.count = 1;
            reg.regType = modbus_source_config->getTypeRegister();
            reg.slaveId = modbus_source_config->getSlaveId();
            reg.startAddress = modbus_source_config->getStartAddress();
            list_of_registers_[modbus_source_config->getClientId()].push_back(reg);

        }else if(config->getTypeSource() == "Mqtt"){
            auto mqtt_source_config = dynamic_cast<MqttSourceConfig*>(config.get());

        }else if(config->getTypeSource() == "Opc"){

        }

    }

    for(const auto& client : clientById_){
        auto client_id = client.first;
        auto reg_list = list_of_registers_.find(client_id);
        
        if(reg_list == list_of_registers_.end()){
            continue;
        }

        plcWorkerById_.emplace(client_id, std::make_unique<PlcWorker>(
            *client.second, reg_list->second));
    }
}

void CompositionRoot::initSources(const AppConfig& cfg)
{
    if(modbusClientById_.empty()){
        throw std::runtime_error("No TCP clients available");
    }

    for(const auto& it : cfg.sourceConfigs_){

        if(it->getTypeSource() == "Modbus"){

            auto modbusSourceConfig = dynamic_cast<ModbusSourceConfig*>(it.get());
            auto idClient = modbusSourceConfig->getClientId();
            auto it = clientById_.find(idClient);
            auto plcWorker = plcWorkerById_.find(idClient);

            if(it == clientById_.end()){
                throw std::runtime_error("No TCP clients available");
            }

            sourceById_.emplace(modbusSourceConfig->getSourceId(),
            std::make_unique<ModbusSource>(*modbusSourceConfig, *(it->second),*(plcWorker->second)));  

        }else if(it->getTypeSource() == "Mqtt"){

            auto mqttSourceConfig = dynamic_cast<MqttSourceConfig*>(it.get());
            
            sourceById_.emplace(mqttSourceConfig->getSourceId(),
            std::make_unique<MqttSource> (*(mqttSourceConfig), *(mqtt_worker_)));

        }
    }
}

void CompositionRoot::initRules(const AppConfig &cfg)
{

    for(const auto& config : cfg.ruleConfigs_){
        const RuleType type = config->getRuleType();
        const auto& sensor = sensorById_.find(config->getSensorId());
        const auto& actuator = iActuatorById_.find(config->getActuatorId());
        auto& state = sensor->second->state();

        if(sensor == sensorById_.end()){
            throw std::runtime_error("Sensor not found for rule: " + config->getSensorId());
        }

        if(actuator == iActuatorById_.end()){
            throw std::runtime_error("Actuator not found for rule: " + config->getActuatorId());
        }

        switch (type)
        {
        case RuleType::Thermostat:{
            
            auto& thermostatConfig = static_cast<const RuleThermostatConfig&>(*config);

            engine_->addRule(std::make_unique<RuleThermostat>(state, *(actuator->second), thermostatConfig));
                break;
            }
        case RuleType::Light:{

            const auto& lightConfig = static_cast<const RuleConfigLight&>(*config);
            
            engine_->addRule(
                std::make_unique<RuleControlLight>(state, *(actuator->second), lightConfig));
                break;
            }
        }
    }
}

void CompositionRoot::initModbusClient(const AppConfig &cfg)
{
    for(const auto& config : cfg.modbusClientConfig_){
        modbusClientById_.emplace(
            config.getClientId(), std::make_shared<ModbusClient>(config)
        );
    }
}

void CompositionRoot::initMqttCommandPublisher(const AppConfig &cfg)
{
}

void CompositionRoot::initIactuators(const AppConfig &cfg)
{
    for(const auto& config : cfg.baseActuatorConfig_){

        std::shared_ptr<ITransport> transport;
        
        auto connect_type = config->getConnectionType();
        
        if(connect_type == ActuatorConnectionType::Modbus){
            
            auto client = modbusClientById_.find(config->getClient_id());
            
            if(client == modbusClientById_.end()){
                throw std::runtime_error("Modbus client not found");
            }

            transport = std::make_shared<ModbusTransport>(*(client->second));

            iActuatorById_.emplace(config->getIdActuator(),
                std::make_unique<GenericActuator>(config, transport));

        }else if(connect_type == ActuatorConnectionType::Mqtt){

            if(!mqtt_client_){
                throw std::runtime_error("MQTT client is not initialized (nullptr)");
            }

            transport = std::make_shared<MqttTransport>(*(mqtt_client_));

            iActuatorById_.emplace(config->getIdActuator(),
                std::make_unique<GenericActuator>(config, transport));   
        }else{

            throw std::runtime_error("Transport initialization failed: no such connection type");
        }
    }
}

void CompositionRoot::initMqttClient(const AppConfig& cfg)
{
    mqtt_client_ = std::make_unique<MqttClient>(cfg.addr, cfg.id);
}

void CompositionRoot::initMqttWorker()
{
    if(!mqtt_client_) {
        throw std::runtime_error("MQTT client is not initialized");
    };
    mqtt_worker_ = std::make_unique<MqttWorker>((*mqtt_client_));
}

void CompositionRoot::init(const AppConfig& cfg)
{
    initLogger();
    initArchive();
    initPgArchive();
    initClients(cfg);
    initMqttClient(cfg);
    initMqttWorker();
    initModbusClient(cfg);
    initPlcWorker(cfg);
    initSources(cfg);
    initSensors(cfg);
    //initActuators(cfg);
    initIactuators(cfg);    
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
    std::cout << "actuator=" << actuatorById_.size() << std::endl;
    for(const auto& actuator : actuatorById_){
        actuator.second->print();
    }
}

void CompositionRoot::printRule() const
{
    std::cout << "Rule: " << ruleById_.size() << std::endl;
}
