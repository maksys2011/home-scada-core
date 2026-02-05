#pragma once

#include "Rule.hpp"
#include "Enum.hpp"

class SensorState;
class Actuator;
class RuleConfigLight;

class RuleLighting : public Rule
{
public:
    RuleLighting(
        SensorState& sensor,
        Actuator& actuator,
        const RuleConfigLight& config);

    void evaluate() override;

private:
    SensorState& sensor_;
    Actuator& actuator_;
    const RuleConfigLight& config_;
    ControlMode selected;
};