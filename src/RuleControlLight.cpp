#include <thread>
#include "RuleControlLight.hpp"
#include "RuleConfigLight.hpp"
#include "Actuator.hpp"
#include "Sensor.hpp"


RuleControlLight::RuleControlLight(
    SensorState &sensor, 
    Actuator &actuator, 
    const RuleConfigLight &config)
    :
    sensor_(sensor),
    actuator_(actuator),
    config_(config)
{}

void RuleControlLight::evaluate()
{
    if(!config_.getEnabled()) return;

    if(selected_ == ControlMode::Manual) return;

    auto valueOpt = sensor_.lastValue();

    if(!valueOpt) return;

    double value = *valueOpt;
    const size_t min = config_.getTargetIlluminance() - 10;
    const size_t max = config_.getTargetIlluminance() + 10;
    const auto& night = config_.getNinght();
    const auto& day = config_.getDay();
    bool isnight =(currentTime_ >= night.fromHour || currentTime_ < night.toHour);
    const TimeWindow& window = isnight ? night : day;

    if(window.fixedPosition == -1){
        if(value < min) {
            actuator_.setPosition(currentPosition_ + 10);
            currentPosition_ += 10;
            return;}
        else if(value > max){
            actuator_.setPosition(currentPosition_ - 10);
            currentPosition_ -= 10;
            return;
        }
    }

    std::cout << "[ACTUATOR]= " << actuator_.config().getId() << " fixedPosition "  << window.fixedPosition << "\n";
}
