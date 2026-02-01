#pragma once

#include "Rule.hpp"

class SensorState;
class Actuator;
class RuleThermostatConfig;

class RuleThermostat : public Rule
{
public:
    RuleThermostat(
        SensorState& sensor,
        Actuator& actuator,
        const RuleThermostatConfig& ruleCfg);

        void evaluate() override;

private:
    SensorState& sensor_;
    Actuator& actuator_;
    const RuleThermostatConfig& ruleCfg_;
};