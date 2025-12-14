#pragma once
#include <string>
#include <Enum.hpp>
#include <fstream>

class Logger
{
public:

    explicit Logger(const std::string& filePath);
    Logger (const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    ~Logger();

    void logStateChange(
        const std::string& sensorId,
        State from,
        State to,
        double value
    );

private:

    std::ofstream file_;
};