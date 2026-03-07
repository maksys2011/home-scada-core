#pragma once
#include "CompositionRoot.hpp"

class Application
{
public:
    Application(
        const AppConfig& cfg, 
        const ConfigLoader configs, 
        CompositionRoot& root);
    void run();
private:
    void init();
    CompositionRoot& root_;
    const AppConfig& cfg_;
    const ConfigLoader& configs_;
};