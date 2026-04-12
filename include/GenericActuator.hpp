#pragma once
#include <string>
#include <memory>
#include "IActuator.hpp" 
#include "ITransport.hpp"
#include "ActuatorConfig.hpp"

class GenericActuator : public IActuator
{
 public:
	GenericActuator (const ActuatorConfig& config,
			std::shared_ptr<ITransport> transport);

	const std::string& getId() const override { return config_.getId(); };
	const std::string& getName() const override { return config_.getName(); };
	bool execute (CommandType cmd, const CommandValue& val) override;
	CommandType getCmd() const override { return config_.getCmd(); };
	bool getState() const override { return state_; };
	void setState(bool state) override;
	void print() const override;

private:
	ActuatorConfig config_;
	std::shared_ptr<ITransport> transport_; 
	CommandType typeCmd = CommandType::Unknown;
	bool success_ = false;
	bool state_ = false;
	int expectedIndex_  = 0;
};