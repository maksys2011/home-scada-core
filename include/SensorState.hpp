#pragma once
#include  <optional>
#include  <string>
#include <Enum.hpp>

class SensorConfig;

class SensorState {
public:

    explicit SensorState(const SensorConfig& config);

    void processValue(double raw);

    State status() const;
    std::optional<double>lastValue() const;

    void print();

    State classify(double raw) const;

private:
    const SensorConfig& config_;
    std::optional<double> lastValue_;
    State currentState = State::INVALID;
    State pendingState;
    size_t debounceCounter;
    size_t debounceLimit;
};