#include "Sensor.hpp"
#include "Enum.hpp"
#include "Logger.hpp"
#include "Archive.hpp"
#include "Source.hpp"
#include <iostream>

Sensor::Sensor(const SensorConfig &config, Logger *logger, Archive *arch, Source *source) 
        : config_(config),
        state_(config, logger, arch),
        source_(source)
{}
void Sensor::updateValue(double rawValue)
{
    state_.processValue(rawValue);
}
void Sensor::update()
{
    if(!source_) return;

    double value = source_->readValue();
    state_.processValue(value);
}
const SensorConfig &Sensor::config() const
{
    return config_;
}
SensorState& Sensor::state()
{
    return state_;
}
void Sensor::print() const
{
    std::cout << "Sensor ID: " << config_.getId() << std::endl <<
                    "Sensor State: " << StateToString(state_.status()) << std::endl;
    if (state_.lastValue()) {
        std::cout << "Value: " << *state_.lastValue();
    }
    std::cout << std::endl;
}

Source *Sensor::getSourse() const
{
    return source_;
}

