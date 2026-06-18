#pragma once

#include "Rule.hpp"

class SensorState;
class Actuator;
class RuleThermostatConfig;
class IActuator;
class ISensorState;

class RuleThermostat : public Rule
{
public:
    RuleThermostat(
        ISensorState& sensor,
        // SensorState& sensor,
        IActuator& actuator,
        const RuleThermostatConfig& ruleCfg);

    void evaluate() override;

private:
    ISensorState& sensor_;
    // SensorState& sensor_;
    IActuator& actuator_;
    const RuleThermostatConfig& ruleCfg_;
};