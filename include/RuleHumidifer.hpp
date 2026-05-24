#pragma once
#include <Rule.hpp>

class SensorState;
class RuleHumidifierConfig;
class IActuator;

class RuleHumidifer : public Rule
{
public:
    RuleHumidifer(SensorState& state,
        IActuator& actuator,
        const RuleHumidifierConfig& config);

    void evaluate() override;

private:
    SensorState& state_;
    IActuator& actuator_;
    const RuleHumidifierConfig& config_;
};