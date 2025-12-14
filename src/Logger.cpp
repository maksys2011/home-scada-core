#include "Logger.hpp"
#include <iostream>
#include <chrono>
#include <iomanip>
#include <filesystem>

Logger::Logger(const std::string &filePath)
{
    /*std::filesystem::path p(filePath);
    std::filesystem::create_directories(p.parent_path()); */
    file_.open(filePath, std::ios::app);
    if(!file_.is_open()){
        std::cerr << "Logger cannot open file: " << filePath << std::endl;
    }
}

Logger::~Logger()
{
    if(file_.is_open()){
        file_.close();
    }
}

void Logger::logStateChange(const std::string& sensorId, State from, State to, double value)
{
    if(!file_.is_open()) return;
    auto now = std::chrono::system_clock::now();
    auto t = std::chrono::system_clock::to_time_t(now);

    file_
        << "[" << std::put_time(std::localtime(&t), "%Y-%m-%d %H:%M:%S") << "] "
        << "[" << sensorId << "] "
        << StateToString(from) <<" -> " << StateToString(to)
        << " | value=" << value << std::endl;
}