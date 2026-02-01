#include "RuleThermostat.hpp"
#include "SensorState.hpp"
#include "Actuator.hpp"
#include "RuleThermostatConfig.hpp"

RuleThermostat::RuleThermostat(
    SensorState &sensor, 
    Actuator& actuator, 
    const RuleThermostatConfig &ruleCfg):
    sensor_(sensor),
    actuator_(actuator),
    ruleCfg_(ruleCfg)
{}

void RuleThermostat::evaluate()
{
    auto valueOpt = sensor_.lastValue();
    if(!valueOpt){
        return;
    }

    double value = *valueOpt;
    
    if(value < ruleCfg_.getMinTemp()){
        actuator_.turnOn();
    }else if(value > ruleCfg_.getMaxTemp()){
        actuator_.turnOff();
    }else{
        return;
    }

}
