#pragma once

#include "Rule.hpp"

class SensorState;
class Actuator;
class RuleThermostatConfig;
class IActuator;

class RuleThermostat : public Rule
{
public:
    RuleThermostat(
        SensorState& sensor,
        IActuator& actuator,
        const RuleThermostatConfig& ruleCfg);

    void evaluate() override;

private:
    SensorState& sensor_;
    IActuator& actuator_;
    const RuleThermostatConfig& ruleCfg_;
};