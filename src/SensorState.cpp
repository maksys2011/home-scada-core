#include  <SensorState.hpp>
#include  <SensorConfig.hpp>
#include  <Enum.hpp>
#include  <iostream>
#include  <Logger.hpp>
#include  <Archive.hpp>

SensorState::SensorState(const SensorConfig &config, Logger* logger, Archive* arch)
    : config_(config),
        currentState(State::OK),
        pendingState(State::OK),
        debounceCounter(0),
        debounceLimit(1),
        logger_(logger),
        arch_(arch)
{}
void SensorState::processValue(double raw)
{
    bool isFirst = !lastValue_.has_value();
    if(!isFirst){
        double diff = std::abs(raw - lastValue_.value());
        if(diff < config_.getNoiseEpsilon()){
            return;
        }
    }

    if(classifyDataQuality(raw) == State::INVALID){
        return;
    }

    lastValue_ = raw;
    State newState = classifyAlarmState(raw);
        
    if(arch_){
        arch_->appendArchive(
            config_.getId(),
            config_.getName(),
            raw,
            currentState
        );
    }

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
    }

    if (pendingState != newState) {
        pendingState = newState;
        debounceCounter = 1;
        return;
    }

    debounceCounter++;
    if (debounceCounter < debounceLimit) {
        return;
    }

    State oldState = currentState;
    currentState = newState;
    pendingState = currentState;
    debounceCounter = 0;

    if (logger_) {
        logger_->logStateChange(
            config_.getId(),
            oldState,
            currentState,
            raw
        );
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

State SensorState::classifyDataQuality(double raw) const
{
    if(!config_.validateValue(raw)){
        return State::INVALID;
    }else return State::OK;
}

State SensorState::classifyAlarmState(double raw) const
{
    if (raw < config_.getAlarmLow() || raw > config_.getAlarmHigh()) return State::ALARM;
    if (raw < config_.getWarnLow() || raw > config_.getWarnHigh()) return State::WARN;
    return State::OK;
}
