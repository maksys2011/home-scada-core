#include  <SensorState.hpp>
#include  <SensorConfig.hpp>
#include  <Enum.hpp>
#include  <iostream>
#include <Logger.hpp>

SensorState::SensorState(const SensorConfig &config, Logger* logger)
    : config_(config),
        currentState(State::OK),
        pendingState(State::OK),
        debounceCounter(0),
        debounceLimit(1),
        logger_(logger)
{}
void SensorState::processValue(double raw)
{
    if(lastValue_.has_value()){
        double diff = std::abs(raw - lastValue_.value());
        if(diff < config_.deadband()){
            return;
        }
    }
    lastValue_ = raw;
    State newState = classify(raw);
    // Как это работает (на примере температуры):

    /*Заданная температура (Уставка): Например, 25°C.
    Гистерезис: Допустим, 2°C.
    Включение: Нагреватель включится, когда температура упадет до 23°C (25°C - 2°C).
    Выключение: Нагреватель выключится, когда температура достигнет 25°C (уставки).
    Результат: Система не будет постоянно включаться и выключаться при малейших колебаниях,
    а будет работать в заданном диапазоне, экономя энергию и ресурс реле */

    if (currentState == State::WARN && newState == State::OK) {
        if (raw >= (config_.getWarnHigh() - config_.hysteresis()) ||
            raw <= (config_.getWarnLow() + config_.hysteresis())) {
            newState = State::WARN;
        }
    }

    if (currentState == State::ALARM && newState == State::WARN) {
        if (raw >= (config_.getAlarmHigh() - config_.hysteresis()) ||
            raw <= (config_.getAlarmLow() + config_.hysteresis())) {
            newState = State::ALARM;
        }
    }

    if (newState == currentState) {
        pendingState = currentState;
        debounceCounter = 0;
    }else {
        if (pendingState != newState) {
            pendingState = newState;
            debounceCounter = 1;
        }else {
            debounceCounter++;
            if (debounceCounter >= debounceLimit) {
                currentState = newState;
                pendingState = currentState;
                debounceCounter = 0;
            }
        }
    }

    if(debounceCounter >= debounceLimit){
        if(logger_){
            logger_->logStateChange(
                config_.getId(),
                currentState,
                newState,
                raw
            );
        }
    }

}
State SensorState::status() const
{
    return currentState;
}
std::optional<double> SensorState::lastValue() const
{
    return lastValue_;
}



void SensorState::print() 
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
