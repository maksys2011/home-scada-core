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

enum class ActuatorConnectionType
{
    Unknown = 0,
    Modbus,
    Mqtt,
    OpcUa
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

enum class ModbusRegisterType
{
    Unknown = 0,
    Coil,
    DiscreteInput,
    InputRegister,
    HoldingRegister
};

enum class RuleType
{
    Thermostat,
    Light
};

enum class SourceType
{
    Unknown = 0,
    Modbus,
    Mqtt,
    OpcUa,
};

enum class CommandType
{
    Unknown = 0,
    Turn,
    SetPosition,
    Reset
};

SensorType ParseSensorType(const std::string &typeStr);

std::string SensorTypeToString(const SensorType type);

ActuatorType ParseActuatorType(const std::string &typeStr);

std::string ActuatorTypeToString(ActuatorType type);

std::string StateToString(State state);

State ParseState(const std::string str);

std::string ModbusRegisterTypeToString(const ModbusRegisterType type);

ModbusRegisterType ParseModbusRegisterType(const std::string& type);

RuleType ParseRuleType(const std::string& type);

std::string RuleTypeToString(const RuleType type);

std::string ParseSourceTypeToString(SourceType& type);

SourceType ParceSourceType(const std::string& type);