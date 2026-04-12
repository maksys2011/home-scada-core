#pragma once
#include <string>
#include <variant>
#include "Enum.hpp"

using CommandValue = std::variant<bool, int, double, std::string>;

class IActuator
{
public:
    virtual ~IActuator() = default;

    virtual const std::string& getId() const = 0;
    virtual const std::string& getName() const = 0;
    virtual bool execute(CommandType cmd, const CommandValue& val) = 0;
    virtual CommandType getCmd() const = 0;
    virtual bool getState() const = 0;
    virtual void setState(bool state) = 0;
    virtual void print() const = 0;
};