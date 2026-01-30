#pragma once
#include <string>
#include <Enum.hpp>
#include <fstream>
#include <filesystem>

class Logger
{
public:

    explicit Logger(const std::string& filePath);
    explicit Logger(const std::filesystem::path& filePath);
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