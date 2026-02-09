#pragma once

#include "Rule.hpp"
#include "Enum.hpp"

class SensorState;
class Actuator;
class RuleConfigLight;

class RuleControlLight : public Rule
{
public:
    RuleControlLight(
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