#pragma once
#include <string>
#include <Enum.hpp>

class Logger
{
    public:
    void logStateChange(
        const std::string sensorId,
        State from,
        State to,
        double value
    );
};