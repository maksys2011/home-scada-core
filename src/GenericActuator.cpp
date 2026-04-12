#include "GenericActuator.hpp"
#include <iostream>

GenericActuator::GenericActuator (
	const ActuatorConfig& config,
	std::shared_ptr<ITransport> transport) :
	config_(config),
	transport_(transport){

	typeCmd = config_.getCmd();
	expectedIndex_  = config_.getExpectedIndex();
}

bool GenericActuator::execute(
	CommandType cmd, 
	const CommandValue& val){
	
	if(val.index() != expectedIndex_){
		std::cerr << "[Actuator Error] ID: " << config_.getId() 
                  		<< " - Wrong data type index. Expected: " << expectedIndex_ 
                 		<< " Got: " << val.index() << std::endl;
		success_ = false;
		return false;
	}

	if(cmd != typeCmd) {
		return false;
	}

    std::string target = std::to_string(config_.getStartAddress());

	if(transport_ && transport_->send(target, val)){
		success_ = true;
		return true;
	}

	success_ = false;
	return false;	
}

void GenericActuator::setState(bool state)
{
	state_ = state;
}

void GenericActuator::print() const
{
}
