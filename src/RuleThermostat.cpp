#include "RuleThermostat.hpp"
#include "SensorState.hpp"
#include "Actuator.hpp"
#include "RuleThermostatConfig.hpp"
#include "IActuator.hpp"

RuleThermostat::RuleThermostat(
    SensorState &sensor, 
    IActuator& actuator, 
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
        actuator_.execute(actuator_.getCmd(), true);
        actuator_.setState(true);
    }else if(value > ruleCfg_.getMaxTemp()){
        actuator_.execute(actuator_.getCmd(), false);
        actuator_.setState(false);
    }else{
        return;
    }
}
