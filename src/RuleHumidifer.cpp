#include "RuleHumidifer.hpp"
#include "SensorState.hpp"
#include "IActuator.hpp"
#include "RuleHumidifierConfig.hpp"
#include <iostream>

RuleHumidifer::RuleHumidifer(SensorState &state, 
    IActuator &actuator, 
    const RuleHumidifierConfig &config)
    :
    state_(state), actuator_(actuator), config_(config)
{}

void RuleHumidifer::evaluate()
{
    auto value = state_.lastValue();

    if(!value) return;

    auto min_value = config_.getMinHumidity();
    auto max_value = config_.getMaxHumidity();

    if(value.has_value() < min_value){

        actuator_.execute(actuator_.getCmd(), true);

        actuator_.setState(true);
        
    }else if(value.has_value() > max_value){

        actuator_.execute(actuator_.getCmd(), false);

        actuator_.setState(false);
    }

}

    
