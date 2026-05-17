#include "GenericActuator.hpp"
#include "ModbusActuatorConfig.hpp"
#include "MqttActuatorConfig.hpp"
#include <iostream>

GenericActuator::GenericActuator (
	std::shared_ptr<BaseActuatorConfig> cfg,
	std::shared_ptr<ITransport> transport) :
	cfg_(std::move(cfg)),
	transport_(transport)
{

	if (!cfg_) {
    	throw std::runtime_error("Configuration pointer is null in GenericActuator");
	}

	typeCmd = cfg_->getCmd();
	expectedIndex_  = cfg_->getExpectedIndex();
}

bool GenericActuator::execute(
    CommandType cmd,
    const CommandValue &val)
{

    if(val.index() != expectedIndex_){
		std::cerr << "[Actuator Error] ID: " << cfg_->getIdActuator()
                  		<< " - Wrong data type index. Expected: " << expectedIndex_ 
                 		<< " Got: " << val.index() << std::endl;
		success_ = false;
		return false;
	}

	if(cmd != typeCmd) {
		return false;
	}


	auto connection_type = cfg_->getConnectionType();

	if(connection_type == ActuatorConnectionType::Modbus){

		auto config = dynamic_cast<ModbusActuatorConfig*>(cfg_.get());

	   	std::string target = std::to_string(config->getStartAddress());

		if(transport_ && transport_->send(target, val)){
			success_ = true;
			return true;
		}

		success_ = false;
		return false;

	}else if(connection_type == ActuatorConnectionType::Mqtt){
		
		auto config_mqtt = dynamic_cast<MqttActuatorConfig*>(cfg_.get());

		std::string target = config_mqtt->getTopic();

		if(transport_ && transport_->send(target, val)){
			success_ = true;
			return true;
		}
	}

	return false;
}

void GenericActuator::setState(bool state)
{
	state_ = state;
}

void GenericActuator::print() const
{
}
