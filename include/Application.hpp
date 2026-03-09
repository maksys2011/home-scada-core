#pragma once
#include "CompositionRoot.hpp"

class Application
{
public:
    Application(
        const AppConfig& cfg, 
        const ConfigLoader& configs, 
        CompositionRoot& root);
    void run();
private:
    void tick();
    void init();

    void updateSensors();
    void evaluateRules();
    void renderConsole();

    CompositionRoot& root_;
    const AppConfig& cfg_;
    const ConfigLoader& configs_;
    std::time_t now_ = std::time(nullptr);
};