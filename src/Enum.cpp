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

