#pragma once
#include  <optional>
#include  <string>
#include <Enum.hpp>
#include <memory>

class SensorConfig;
class Logger;

class SensorState {
public:

    explicit SensorState(const SensorConfig& config, Logger* logger);

    void processValue(double raw);

    State status() const;

    std::optional<double>lastValue() const;

    double getdebounceLimit() const {return debounceLimit;}

    void print();

    State classify(double raw) const;


private:
    const SensorConfig& config_;
    std::optional<double> lastValue_;
    State currentState = State::INVALID;
    State pendingState;
    size_t debounceCounter;
    size_t debounceLimit;
    Logger* logger_;

};