#include <iostream>
#include <thread>
#include <chrono>
#include "Application.hpp"
#include "Sensor.hpp"
#include "Rule.hpp"
#include "RuleEngine.hpp"

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

                        
}
