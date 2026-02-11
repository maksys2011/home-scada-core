#include "RuleControlLight.hpp"
#include "RuleConfigLight.hpp"

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
    auto valueOpt = sensor_.lastValue();
    if(!valueOpt) {
        return;
    }

    double value = *valueOpt;

    const auto& night = config_.getNinght();
    const auto& day = config_.getDay();

    if(currentTime_ > 21 && currentTime_ < 7){
        currentPosition_ = 80;
        targetPosition_ =  80;
        return;
    }
    
    if(selected_ == ControlMode::Manual){
        return;
    }

    









    
    
    


    
}
