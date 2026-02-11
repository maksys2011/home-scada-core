#pragma once

#include "Rule.hpp"
#include "Enum.hpp"
#include "SensorState.hpp"

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
    ControlMode selected_;
    size_t currentPosition_;
    size_t targetPosition_;
    size_t currentTime_;
};