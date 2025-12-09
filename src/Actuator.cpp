#include "Actuator.hpp"
#include <utility>
#include "Enum.hpp"

Actuator::Actuator(ActuatorConfig config):
            config_(std::move(config))
            {}
void Actuator::turnOn()
{
    state_ = true;
}

void Actuator::turnOff()
{
    state_ = false;
}

void Actuator::setValue(double value)
{
    config_.validate();
    currentValue_ = value;
}

bool Actuator::getStatus() const
{
    return state_;
}

double Actuator::getValue() const
{ 
    return currentValue_;
}

const ActuatorConfig &Actuator::config() const
{
    return config_;
}

void Actuator::print() const
{
    std::cout << "Actuator id: " << config_.id_  << std::endl
                << "Name: " << config_.getName() << std::endl
                << "ActuratorType: " << ActuatorTypeToString(config_.type_) << std::endl
                << "State: " << (state_ ?  "ON" : "OFF") << std::endl
                << "CurrentValue: " << getValue() << std::endl;

}
