#pragma once
#include <string>
#include <iostream>
#include "ActuatorConfig.hpp"
#include "ModbusClient.hpp"

class Actuator
{
public:
    explicit Actuator (const ActuatorConfig&  config, ModbusClient& client);
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
    ModbusClient& client_;
    ActuatorConfig config_;
    bool state_ = false;
    double currentValue_ = 0.0;
    double max_settings = 0.0;
    double min_settings = 0.0;
    size_t position_ = 0;
};