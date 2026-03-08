#include <iostream>
#include <thread>
#include <chrono>
#include "Application.hpp"
#include "Sensor.hpp"
#include "Rule.hpp"
#include "RuleEngine.hpp"
#include "Actuator.hpp"

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
    
    for(size_t i = 0; i < 100; ++i){
        
        tick();
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
    
}

void Application::tick()
{
    updateSensors();
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
    /*
    for(const auto& [key, sensor] : root_.getSensorById()){
        auto value = sensor->state().lastValue();
        const std::string& name = sensor->config().getName();
        auto type = std::string_view(name).substr(0, name.find('_'));
            
        if(!value) {
            std::cout << name << " | Данные отсутствуют" << std::endl;
            continue;
        }

        std::string unit = (type == "light") ? " lx" : " \u2103";
        std::string color = (type == "light") ? "\033[33m" : "\033[36m"; 

        std::cout << name << " value= " 
                        << color << std::right << std::setw(6) 
                        << *value << unit << " \033[0m" 
                        << std::endl;
    }
    for(const auto& [key, actuator] : root_.getActuatorById()){
        std::string state = (actuator->getStatus() ? "ON" : "OFF");
        std::string name = actuator->config().getName();
        std::cout << "[" << name << "] state: " << state << std::endl; 
    }
        */
       
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

    std::string unit = (type == "light") ? "lx" : "°C";
    std::string color = (type == "light") ? "\033[33m" : "\033[36m";

    std::cout << std::left << std::setw(25) << name
              << color
              << std::setw(10) << *value
              << "\033[0m"
              << std::setw(5) << unit
              << "\n";
}
std::cout << "\n================ ACTUATORS ================\n";
std::cout << std::left << std::setw(25) << "NAME"
          << std::setw(10) << "STATE"
          << "\n";

std::cout << "-------------------------------------------\n";

for(const auto& [key, actuator] : root_.getActuatorById()){

    std::string state = actuator->getStatus() ? "ON" : "OFF";
    const std::string& name = actuator->config().getName();

    std::string color = actuator->getStatus() ? "\033[32m" : "\033[31m";

    std::cout << std::left << std::setw(25) << name
              << color
              << std::setw(10) << state
              << "\033[0m"
              << "\n";
}
}
