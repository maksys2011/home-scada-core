#include "Sensor.hpp"
#include "Enum.hpp"
#include <iostream>

Sensor::Sensor(const SensorConfig &config)
    : config_(config),
    state_(config)
{}

void Sensor::updateValue(double rawValue)
{
    state_.processValue(rawValue);
}

const SensorConfig & Sensor::config() const
{
    return config_;
}

State Sensor::state() const
{
    return state_.status();
}

void Sensor::print() const
{
    std::cout << "Sensor ID: " <<
                config_.getId() <<
                    " " << StateToString(state_.status());
    if (state_.lastValue()) {
        std::cout << "Value: " << *state_.lastValue();
    }
    std::cout << std::endl;
}
