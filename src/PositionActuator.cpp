#include <iostream>
#include "PositionActuator.hpp"
#include "ModbusActuatorConfig.hpp"
#include "MqttActuatorConfig.hpp"

PositionActuator::PositionActuator(
    std::shared_ptr<ITransport> transport, 
    std::shared_ptr<BaseActuatorConfig> cfg)
    :
    transport_(transport),
    cfg_(cfg)
{}

bool PositionActuator::execute(CommandType cmd, const CommandValue &val)
{
    if(val.index() != expectedIndex_){
	    std::cerr << "[Actuator Error] ID: " << cfg_->getIdActuator()
                  		<< " - Wrong data type index. Expected: " << expectedIndex_ 
                 		<< " Got: " << val.index() << std::endl;
	    success_ = false;
		return false;
	}
    
    if(cmd != typeCmd){
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

void PositionActuator::setState(bool state)
{
}

void PositionActuator::print() const
{
}
