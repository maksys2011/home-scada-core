#pragma once
#include "ActuatorConfig.hpp"
#include <string>
#include <iostream>

class Actuator
{
public:
    explicit Actuator (ActuatorConfig  config);
    void turnOn();
    void turnOff();
    void setValue(double value);
    bool getStatus() const;
    double getValue() const;
    const ActuatorConfig& config() const;
    void print() const;
    bool getStateActuator();
    void setPosition(int perсent);
    size_t getPosition() const {return position_;};

private:

    ActuatorConfig config_;
    bool state_ = false;
    double currentValue_ = 0.0;
    double max_settings = 0.0;
    double min_settings = 0.0;
    size_t position_ = 0;
};