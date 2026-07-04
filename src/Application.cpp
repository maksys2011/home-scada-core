#include <iostream>
#include <thread>
#include <chrono>
#include <ctime>
#include "Application.hpp"
#include "Sensor.hpp"
#include "Rule.hpp"
#include "RuleEngine.hpp"
#include "Actuator.hpp"
#include "IActuator.hpp"
#include "PlcWorker.hpp"
#include "MqttWorker.hpp"
#include "MqttClient.hpp"
#include "Dispatcher.hpp"

Application::Application(
    const AppConfig &cfg, 
    const ConfigLoader& configs,
    CompositionRoot& root)
    : 
    cfg_(cfg),
    configs_(configs),
    root_(root)
{}

void Application::run()
{
    init();

    // modbus client connect 

    for(const auto& client : root_.getClient()){
        client.second->connect();
    }

    // mqtt client connect

    auto& mqtt_client = root_.getClientMqtt();

    mqtt_client->connect(root_.getMqttCollectionTopics());


    for(const auto& plcWorker : root_.getPlcWorkerById()){
        plcWorker.second->start();
    } 

    auto& plcWorkerMqtt = root_.getMqttWorker();

    plcWorkerMqtt->start();

    try
    {
        auto& dispather = root_.getDispatsher();

        for(size_t i = 0; i < 10; ++i){  

            tick();

            std::this_thread::sleep_for(std::chrono::seconds(3));
        }
    }
    catch(const std::exception& e)
    {
        for(const auto& plcWorker : root_.getPlcWorkerById()){
            plcWorker.second->stop();
        }

        plcWorkerMqtt->stop();

        throw;
    }

    for(const auto& plcWorker : root_.getPlcWorkerById()){
        plcWorker.second->stop();
    }

    plcWorkerMqtt->stop();
}

void Application::tick()
{
    updateSensors();

    auto& dispather = root_.getDispatsher();

    for(const auto& sensor : root_.getSensorById()){
        
        const auto& sensorstate = sensor.second->state();

        const auto snapshot = sensorstate.getSnapShot();    

        dispather->publishetValid(snapshot);

    }

    evaluateRules();

    renderConsole();
}

void Application::init()
{
    root_.init(cfg_);
}

void Application::updateSensors()
{
    for(const auto& [key, sensor] : root_.getSensorById()){

        sensor->update();
        
    }  
}

void Application::evaluateRules()
{
    root_.getRuleEngine()->evaluate();
}

void Application::renderConsole()
{ 
    std::tm* local_time = std::localtime(&now_);
    std::cout << "Текущее время: " 
              << local_time->tm_hour << ":" 
              << local_time->tm_min << ":" 
              << local_time->tm_sec << std::endl;
    
    std::cout << "\n================= SENSORS =================\n";
    std::cout << std::left << std::setw(25) << "NAME"
        << std::setw(10) << "VALUE"
        << std::setw(5) << "UNIT"
        << "\n";

    std::cout << "-------------------------------------------\n";

    for(const auto& [key, sensor] : root_.getSensorById()){

        auto value = sensor->state().lastValue();
        const std::string& name = sensor->config().getName();
        auto type = std::string_view(name).substr(0, name.find('_'));

        if(!value){
            std::cout << std::left << std::setw(25) << name
                  << std::setw(10) << "N/A"
                  << "\n";
            continue;
        }

        std::string sensor_unit = ParseSensorUnitToString(sensor->config().getSensorUnit());

        std::string unit{};
        
        if(sensor_unit == "celsius"){
            unit = "°C";
        }else if(sensor_unit == "lux"){
            unit = "lx";
        }else if(sensor_unit == "percentage"){
            unit = "%";
        }

        std::string color = (type == "light") ? "\033[33m" : "\033[36m";

        std::cout << std::left << std::setw(25) << name
            << color
            << std::setw(10) << *value
            << "\033[0m"
            << std::setw(5) << unit
            << "\n";
    }
    std::cout << "\n================ ACTUATORS ================\n";
    std::cout << std::left << std::setw(25) << "ID-ACTUATOR"
        << std::setw(10) << "STATE"
        << "\n";

    std::cout << "-------------------------------------------\n";

    for(const auto& [key, actuator] : root_.getIActuatorById()){ 

        std::string state = actuator->getState() ? "ON" : "OFF";

        const std::string& name = actuator->getId();

        std::string color = actuator->getState() ? "\033[32m" : "\033[31m";

        std::cout << std::left << std::setw(25) << name
            << color
            << std::setw(10) << state
            << "\033[0m"
            << "\n";
}
    std::cout << std::endl;
}
