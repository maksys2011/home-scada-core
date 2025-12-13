#include "Logger.hpp"
#include <iostream>

void Logger::logStateChange(const std::string sensorId, State from, State to, double value)
{
    std::cout << "[" << sensorId << "]" <<
        StateToString(from) << " -> " << StateToString(to) << " "
        << " | value " << value << std::endl;
}