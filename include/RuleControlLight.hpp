#pragma once

#include "Rule.hpp"
#include "Enum.hpp"
#include "SensorState.hpp"

class SensorState;
class Actuator;
class RuleConfigLight;
class IActuator;

class RuleControlLight : public Rule
{
public:
    RuleControlLight(
        ISensorState& sensor,
        IActuator& actuator,
        const RuleConfigLight& config,
        int start_position_ = 0);

    void evaluate() override;
    bool getIsSuccess() { return isSuccess_; };

private:
    ISensorState& sensor_;
    IActuator& actuator_;
    const RuleConfigLight& config_;
    ControlMode selected_ = ControlMode::Auto;
    int currentPosition_ = 0;
    size_t targetPosition_ = 0;
    size_t currentTime_ = 0;
    bool isSuccess_ = false;
};