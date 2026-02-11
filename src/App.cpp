#include <vector>
#include <sstream>
#include <thread>
#include <iomanip>

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
#include "RandomSource.hpp"

App::App() = default;

void App::run(AppConfig&& cfg)
{
    init(std::move(cfg));

    for(size_t i = 0; i < 10; ++i){
        std::cout << "\n";
        tick();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void App::init(AppConfig&& cfg)
{
    logger_  = std::make_unique<Logger>(cfg_.getPaths().fileLoggerPath);
    archive_ = std::make_unique<Archive>(cfg_.getPaths().fileArhivePath);
    sourse2_ = std::make_unique<RandomSource>(15.0, 25.0);
    cfg = cfg_.load();
 
    for(const auto& config : cfg.sensorConfigs_){
        sensor_ = std::make_unique<Sensor>(
            config,
            logger_.get(),
            archive_.get(),
            sourse2_.get()
        );
        sensorById_.emplace(config.getId(), std::move(sensor_));
    }

    for(const auto& actConfig : cfg.actuatorConfigs_){
        actuator_ = std::make_unique<Actuator>(
            actConfig
        );
        actuatorById_.emplace(actConfig.getId(), std::move(actuator_));
    } 

    engine_ = std::make_unique<RuleEngine>();

    for (const auto& ruleCfgBase : cfg.ruleConfigs_) {
        if (auto* thermoCfg =
            dynamic_cast<RuleThermostatConfig*>(ruleCfgBase.get())) {
            auto sensorIt = sensorById_.find(thermoCfg->getIdSensor());
            auto actIt    = actuatorById_.find(thermoCfg->getIdActuator());
            if (sensorIt == sensorById_.end() ||
                actIt    == actuatorById_.end()) {

                throw std::runtime_error(
                    "RuleThermostat: invalid sensor or actuator id"
                );
            }
            engine_->addRule(
                std::make_unique<RuleThermostat>(
                    sensorIt->second->state(),
                    *actIt->second,
                    *thermoCfg
                )
            );
        }  
}
}   

void App::tick()
{
    for(auto& [id, sensor] : sensorById_){
        sensor->update();
        auto val = sensor->state().lastValue();
        if(val){
            std::cout << "[SENSOR] id=" << id  <<
            " value= " << std::fixed << std::setprecision(2) <<
            *val << "\n";
        }
    }
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
    if(actuatorById_.count(id)){
        actuatorById_[id]->turnOn();
    }
}

void App::turnOffActuator(const std::string &id)
{   
    if(actuatorById_.count(id)){
        actuatorById_[id]->turnOn();
    }
}

void App::listActurator() const
{
    for(const auto& it : actuatorById_){
        it.second->print();
        std::cout << "\n";
    }
}
