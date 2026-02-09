#include "RuleControlLight.hpp"

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
    
}
