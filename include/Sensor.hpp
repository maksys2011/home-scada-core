#pragma once
#include <mutex>
#include <thread>
#include <chrono>
#include <atomic>
#include "SensorConfig.hpp"
#include "SensorState.hpp"
#include "Enum.hpp"

class Source;
class Logger;
class Archive;
class PgArchive;

class Sensor {

public:
    explicit  Sensor(const SensorConfig& config, 
                    Logger* logger, 
                    Archive* arch,
                    PgArchive& pgArchive,
                    Source* source);

    void updateValue(double rawValue);
    void update();
    
    const SensorConfig& config() const;
    Source* getSourse() const;
    SensorState& state();
   
    void print() const;
 
private:
    
    const SensorConfig& config_;
    SensorState state_;
    Source* source_;
};

