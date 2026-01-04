#include <vector>
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
{   
    const std::string& fileSensorConfigPath = "/home/maksys2011/home-scada/configTest.json/SensorConfig.json";
    const std::string& fileLoggerPath = "/home/maksys2011/home-scada/logs/events.log";
    const std::string& fileArchivePath = "/home/maksys2011/home-scada/archive/archive.csv";
    const std::string& file = "/home/maksys2011/home-scada/archive/arch.txt";
    const std::string& fileCfgActuator = "/home/maksys2011/home-scada/configTest.json/ActuatorConfig.json";
    const std::string& fileCfgRuleThermostat = "/home/maksys2011/home-scada/configTest.json/RuleThermostat.json";
    std::vector<double> values_ {10.0, 17.0, 16.0, 19.0, 22.0, 23.0, 23.0};
    
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
}

void App::tick()
{
    sensor_->update();
    engine_->evaluate();
}

void App::shutdown()
{
}
