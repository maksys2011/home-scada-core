#pragma once
#include <string>
#include <stdexcept>

enum class SensorType
{
    Analog,
    Digital,
    Counter
};

enum class ActuatorType
{
    Relay, 
    PWM, 
    DigitalOut, 
    AnalogOut
};

enum class State
{
    OK,
    WARN,
    ALARM,
    INVALID
};

SensorType ParseSensorType(const std::string &typeStr);

std::string SensorTypeToString(const SensorType type);

ActuatorType ParseActuatorType(const std::string &typeStr);

std::string ActuatorTypeToString(ActuatorType type);

std::string StateToString(State state);