#include <vector>
#include <sstream>

#include "App.hpp"
#include "Sensor.hpp"
#include "SensorConfig.hpp"
#include "testSource.hpp"
#include "ActuatorConfig.hpp"
#include "Actuator.hpp"
#include "RuleEngine.hpp"
#include "RuleThermostat.hpp"
#include "RuleThermostatConfig.hpp"
#include "Logger.hpp"
#include "Archive.hpp"

App::App() = default;

void App::run()
{
    init();

    for(size_t i = 0; i < source_->getValues().size(); i++){
        tick();
    }
    shutdown();
}

void App::init()
{       ///home/maksys2011/gitclone/home-scada-core/configTest.json/SensorConfig.json
    const std::string& fileSensorConfigPath = "/home/maksys2011/gitclone/home-scada-core/configTest.json/SensorConfig.json";
    const std::string& fileLoggerPath = "/home/maksys2011/gitclone/home-scada-core/logs/events.log";
    const std::string& fileArchivePath = "/home/maksys2011/gitclone/home-scada-core/archive/archive.csv";
    const std::string& file = "/home/maksys2011/gitclone/home-scada-core/archive/arch.txt";
    const std::string& fileCfgActuator = "/home/maksys2011/gitclone/home-scada-core/configTest.json/ActuatorConfig.json";
    const std::string& fileCfgRuleThermostat = "/home/maksys2011/gitclone/home-scada-core/configTest.json/RuleThermostat.json";
    std::vector<double> values_ {10.0, 17.0, 16.0, 19.0, 22.0, 23.0, 23.0};
    
    for(size_t i = 15; i < 5; i++){
        values_.push_back(i);
    }

    values_.push_back(20);
    values_.push_back(19);
    values_.push_back(18);
    values_.push_back(17);
    values_.push_back(16);

    logger_  = std::make_unique<Logger>(fileLoggerPath);
    archive_ = std::make_unique<Archive>(fileArchivePath);
    
    SensorConfig sensorCfg;
    sensorCfg.fromJson(fileSensorConfigPath);
    
    source_  = std::make_unique<testSource>(values_);

    sensor_  = std::make_unique<Sensor>(
        sensorCfg,
        logger_.get(),
        archive_.get(),
        source_.get()
    );

    ActuatorConfig actuatorCfg;
    actuatorCfg.fromJson(fileCfgActuator);
    actuator_ = std::make_unique<Actuator>(actuatorCfg);
    
    ruleCfg_.fromJson(fileCfgRuleThermostat);

    thermoRule_ = std::make_unique<RuleThermostat>(
        sensor_->state(),
        actuator_.get(),
        ruleCfg_
    );

    engine_  = std::make_unique<RuleEngine>();
    engine_->addRule(std::move(thermoRule_));

    actuatorById_[actuatorCfg.getId()] = std::move(actuator_);
}

void App::tick()
{
    sensor_->update();
    engine_->evaluate();
}

void App::shutdown()
{
}

bool App::repl(std::string& line)
{
    return true;
}

void App::printAllActuators()const 
{
    if(!actuatorById_.empty()){
        for(const auto& act : actuatorById_){
            act.second->print();
            std::cout << "\n";
        }
    }
}

void App::printActuatorStatus(const std::string& id)const
{
    if(actuatorById_.count(id)){
        std::cout << "id : " << id << " \n";
        std::cout << "status: " << actuatorById_.find(id)->second->getStatus() << "\n";
    }
}

void App::turnOnActruator(const std::string &id)
{
}

void App::turnOffActuator(const std::string &id)
{
}

void App::listActurator() const
{
}
