#pragma once
#include <string>
#include <memory>
#include "IActuator.hpp" 
#include "ITransport.hpp"
#include "ActuatorConfig.hpp"
#include "BaseActuatorConfig.hpp"

class GenericActuator : public IActuator
{
 public:
	GenericActuator (
		std::shared_ptr<BaseActuatorConfig> cfg,
		std::shared_ptr<ITransport> transport);

	const std::string& getId() const override { return cfg_->getIdActuator(); };
	bool execute (CommandType cmd, const CommandValue& val) override;
	CommandType getCmd() const override { return cfg_->getCmd(); };
	bool getState() const override { return state_; };
	void setState(bool state) override;
	void print() const override;

private:
	std::shared_ptr<BaseActuatorConfig> cfg_;
	std::shared_ptr<ITransport> transport_; 
	CommandType typeCmd = CommandType::Unknown;
	bool success_ = false;
	bool state_ = false;
	int expectedIndex_  = 0;
};