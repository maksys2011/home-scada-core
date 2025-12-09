#include  <SensorState.hpp>
#include  <SensorConfig.hpp>
#include  <Enum.hpp>
#include  <iostream>

SensorState::SensorState(const SensorConfig &config)
    : config_(config)
{}

void SensorState::processValue(double raw)
{
    lastValue_ = raw;
    currentState = classify(raw);
}

State SensorState::status() const
{
    return currentState;
}

std::optional<double> SensorState::lastValue() const
{
    return lastValue_;
}

void SensorState::print() const
{
    std::cerr << "SensorState::print()" << std::endl;
    std::cout << "State: " << StateToString(currentState);
    if (lastValue_) {
        std::cout << ", lastValue: " << lastValue_.value();
    }
    std::cout << std::endl;
}

State SensorState::classify(double raw) const
{
    if (!config_.validateValue(raw)) return State::INVALID;
    if (raw < config_.getAlarmLow() || raw > config_.getAlarmHigh()) return State::ALARM;
    if (raw < config_.getWarnLow() || raw > config_.getWarnHigh()) return State::WARN;
    return State::OK;
}
