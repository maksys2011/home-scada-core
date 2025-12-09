#pragma once
#include  <optional>
#include  <string>
#include <Enum.hpp>

class SensorConfig;

class SensorState {
public:

    explicit SensorState(const SensorConfig& config);

    // обновить значение для классификации OK, WARN, ALARM, INVALID
    void processValue(double raw);

    // геттеры
    State status() const;
    std::optional<double>lastValue() const;

    // печать для отладки
    void print() const;

    // внутренняя класификация (гистерезис + политика)
    State classify(double raw) const;

private:

    const SensorConfig& config_;
    std::optional<double> lastValue_;
    State currentState = State::INVALID;
};