#pragma once
#include  "SensorConfig.hpp"
#include  "SensorState.hpp"
#include  "Enum.hpp"

class Logger;

class Sensor {
public:

    explicit  Sensor(const SensorConfig& config, Logger* logger);

    // Обновление значения (приходит от Source)
    void updateValue(double rawValue);

    const SensorConfig& config() const;

    SensorState state() const;

    void print() const;

private:

    const SensorConfig& config_;
    SensorState state_;
};

