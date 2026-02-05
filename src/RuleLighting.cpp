#include "RuleLighting.hpp"

RuleLighting::RuleLighting(
    SensorState &sensor, 
    Actuator &actuator, 
    const RuleConfigLight &config)
    :
    sensor_(sensor),
    actuator_(actuator),
    config_(config)
{}

void RuleLighting::evaluate()
{
    auto valueOpt = sensor_.lastValue();
    if(!valueOpt) {
        return;
    }
    
}
