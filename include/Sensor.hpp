#pragma once
#include  "SensorConfig.hpp"
#include  "SensorState.hpp"
#include  "Enum.hpp"

class Sensor {
public:

    explicit  Sensor(const SensorConfig& config);

    // Обновление значения (приходит от Source)
    void updateValue(double rawValue);

    const SensorConfig& config() const;

    State state() const;

    void print() const;

private:

    const SensorConfig& config_;
    SensorState state_;
};

