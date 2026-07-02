#pragma once
#include <string>
#include <memory>
#include "IActuator.hpp"
#include "ITransport.hpp"
#include "BaseActuatorConfig.hpp"
#include "Enum.hpp"


class PositionActuator : public IActuator
{
public:
    PositionActuator(
        std::shared_ptr<ITransport> transport,
        std::shared_ptr<BaseActuatorConfig> cfg);

    const std::string& getId() const override { return cfg_->getIdActuator(); };
	bool execute (CommandType cmd, const CommandValue& val) override;
	CommandType getCmd() const override { return cfg_->getCmd(); };
	bool getState() const override { return state_; };
	void setState(bool state) override;
	void print() const override;

    int getPosition() { return current_position_; };

private:
    std::shared_ptr<ITransport> transport_;
    std::shared_ptr<BaseActuatorConfig> cfg_;
    CommandType typeCmd = CommandType::Unknown;
    bool state_ = false;
    bool success_ = false;
    int expectedIndex_ = 0;
    int current_position_ = 0;
};


