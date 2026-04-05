#include <Enum.hpp>

SensorType ParseSensorType(const std::string &typeStr)
{
    if (typeStr == "Analog")
        return SensorType::Analog;
    else if (typeStr == "Digital")
        return SensorType::Digital;
    else if (typeStr == "Counter")
        return SensorType::Counter;
    else
        throw   ("Invalid type string: " + typeStr);
}

std::string SensorTypeToString(const SensorType type)
{
    switch (type)
    {
        case SensorType::Analog:
            return "Analog";
        case SensorType::Digital:
            return "Digital";
        case SensorType::Counter:
            return "Counter";
        default:
            return "Unknown";
    }
}

ActuatorType ParseActuatorType(const std::string &typeStr)
{
    if (typeStr == "Relay")
        return ActuatorType::Relay;
    else if (typeStr == "PWM")
        return ActuatorType::PWM;
    else if (typeStr == "DigitalOut")
        return ActuatorType::DigitalOut;
    else if (typeStr == "AnalogOut")
        return ActuatorType::AnalogOut;
    else
    return ActuatorType();
}

std::string ActuatorTypeToString(const ActuatorType type)
{
    switch (type)
    {
        case ActuatorType::Relay:
            return "Relay";
        case ActuatorType::PWM:
            return "PWM";
        case ActuatorType::DigitalOut:
            return "DigitalOut";
        case ActuatorType::AnalogOut:
            return "AnalogOut";
        default:
            return "Unknown";
    }
    return std::string();
}

std::string StateToString(State state) {
    switch (state)
    {
        case State::OK:
            return "OK";
        case State::WARN:
            return "WARN";
        case State::ALARM:
            return "ALARM";
        case State::INVALID:
            return "INVALID";
    }
        return std::string();
}

State ParseState(const std::string str) {
    if(str == "OK") return State::OK;
    else if(str == "WARN") return State::WARN;
    else if(str == "ALARM") return State::ALARM;
    else if(str == "INVALID") return State::INVALID;
    else return State();
}

std::string ModbusRegisterTypeToString(const ModbusRegisterType type)
{
    switch (type)
    {
    case ModbusRegisterType::Coil: return "coil";
    case ModbusRegisterType::DiscreteInput: return "discreteInput";
    case ModbusRegisterType::HoldingRegister: return "holdingRegister";
    case ModbusRegisterType::InputRegister: return "inputRegister";
    case ModbusRegisterType::Unknown: return "unknowen";
    }
    return std::string();
}

ModbusRegisterType ParseModbusRegisterType(const std::string& type)
{
    if(type == "Coil") return ModbusRegisterType::Coil;
    else if(type == "DiscreteInput") return ModbusRegisterType::DiscreteInput;
    else if(type == "InputRegister") return ModbusRegisterType::InputRegister;
    else if(type == "HoldingRegister") return ModbusRegisterType::HoldingRegister;
    else return ModbusRegisterType::Unknown;
}

RuleType ParseRuleType(const std::string& type)
{
    if(type == "Thermostat") return RuleType::Thermostat;
    else if(type == "Light") return RuleType::Light;
    else throw std::runtime_error("No suitable type rule found");
}

std::string RuleTypeToString(const RuleType type)
{
    switch (type)
    {
    case RuleType::Thermostat: return "Thermostat";
    case RuleType::Light: return "Light";
    }

    return std::string();
}

SourceType ParceSourceType(const std::string &type)
{
    if(type == "Modbus") return SourceType::Modbus;
    else if(type == "Mqtt") return SourceType::Mqtt;
    else if(type == "OpcUa") return SourceType::OpcUa;
    else return SourceType::Unknown;
}

std::string ParseSourceTypeToString(SourceType &type)
{
    switch (type)
    {
    case SourceType::Modbus: return "Modbus";
    case SourceType::Mqtt: return "Mqtt";
    case SourceType::OpcUa: return "OpcUa";
    }
    return std::string();
}
