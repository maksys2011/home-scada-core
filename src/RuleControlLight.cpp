#include <thread>
#include "RuleControlLight.hpp"
#include "RuleConfigLight.hpp"
#include "Actuator.hpp"
#include "Sensor.hpp"
#include "IActuator.hpp"
#include "ISensorState.hpp"


RuleControlLight::RuleControlLight(
    ISensorState &sensor, 
    IActuator &actuator, 
    const RuleConfigLight &config,
    int start_position)
    :
    sensor_(sensor),
    actuator_(actuator),
    config_(config),
    currentPosition_(start_position)

{}

void RuleControlLight::evaluate()
{
    if(!config_.getEnabled()) return;

    if(selected_ == ControlMode::Manual) return;

    auto valueOpt = sensor_.lastValue();

    if(!valueOpt) return;

    double value = *valueOpt;
    const size_t min = config_.getTargetIlluminance() - 10;
    const size_t max = config_.getTargetIlluminance() + 10;
    const auto& night = config_.getNinght();
    const auto& day = config_.getDay();
    bool isnight =(currentTime_ >= night.fromHour || currentTime_ < night.toHour);
    const TimeWindow& window = isnight ? night : day;

    auto command = actuator_.getCmd();

    //isSuccess_ = actuator_.execute(command, 10);

    std::cerr << "current position" << currentPosition_ << std::endl;

    if(window.fixedPosition == -1){
        if(value < min) {
            
            if(currentPosition_ >= 91){
                return;
            }else{
                currentPosition_ += 10;
            }

            std::cout << "current position" << currentPosition_ << std::endl;

            isSuccess_ =  actuator_.execute(command, currentPosition_);

        }
        else if(value > max){

            if(currentPosition_ >= 10){
                currentPosition_ -= 10;
            }

            //std::cout << "current position" << currentPosition_ << std::endl;
            
            isSuccess_ = actuator_.execute(command, currentPosition_);
        }
    }
}
