#pragma once
#include <string>
#include <stdexcept>

enum class SensorType
{
    Analog,    /// double
    Digital,   /// bool
    Counter    /// int64_t
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

enum class ControlMode
{
    Auto,
    Manual
};

enum class ModbusObjectType
{
    Unknowen = 0,
    Coil,
    DiscreteInput,
    InputRegister,
    HoldingRegister
};

SensorType ParseSensorType(const std::string &typeStr);

std::string SensorTypeToString(const SensorType type);

ActuatorType ParseActuatorType(const std::string &typeStr);

std::string ActuatorTypeToString(ActuatorType type);

std::string StateToString(State state);

State ParseState(std::string const str);

std::string ModbusObjectTypeToString(const ModbusObjectType type);

/// @brief  "превращаем строку в обьект ModbusObjectType"
/// @param connectionType 
/// @return 
ModbusObjectType ParseModbusObjectType(const std::string& connectionType);