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

std::string ModbusObjectTypeToString(const ModbusObjectType type)
{
    switch (type)
    {
    case ModbusObjectType::Coil: return "coil";
    case ModbusObjectType::DiscreteInput: return "discretedInput";
    case ModbusObjectType::HoldingRegister: return "holdingRegister";
    case ModbusObjectType::InputRegister: return "inputRegister";
    case ModbusObjectType::Unknowen: return "unknowen";
    }
    return std::string();
}

ModbusObjectType ParseModbusObjectType(const std::string &connectionType)
{
    if(connectionType == "coil") return ModbusObjectType::Coil;
    else if(connectionType == "discreteInput") return ModbusObjectType::DiscreteInput;
    else if(connectionType == "inputRegister") return ModbusObjectType::InputRegister;
    else if(connectionType == "holdingRegister") return ModbusObjectType::HoldingRegister;
    else return ModbusObjectType::Unknowen;
}
