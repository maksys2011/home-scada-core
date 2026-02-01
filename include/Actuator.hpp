#pragma once
#include "ActuatorConfig.hpp"
#include <string>
#include <iostream>

class Actuator
{
public:
    
    explicit Actuator (ActuatorConfig  config);

    //Управление

    void turnOn();
    void turnOff();

    void setValue(double value);

    //Получение статуса

    bool getStatus() const;
    double getValue() const;
    const ActuatorConfig& config() const;

    //Отладка
    
    void print() const;

private:

    ActuatorConfig config_;
    bool state_ = false;
    double currentValue_ = 0.0;

    // Уставки
    double max_settings = 0.0;
    double min_settings = 0.0;

    // 

};