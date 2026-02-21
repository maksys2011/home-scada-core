#pragma once
#include "SensorConfig.hpp"
#include "SensorState.hpp"
#include "Enum.hpp"


class Source;
class Logger;
class Archive;

class Sensor {

public:
    explicit  Sensor(const SensorConfig& config, 
                    Logger* logger, 
                    Archive* arch,
                    Source* source);

    void updateValue(double rawValue);
    void update();
    const SensorConfig& config() const;
    SensorState& state();
    void print() const;
    Source* getSourse() const;

private:
    const SensorConfig& config_;
    SensorState state_;
    Source* source_;
};

