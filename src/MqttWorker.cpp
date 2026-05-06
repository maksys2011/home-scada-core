#include "MqttWorker.hpp"

MqttWorker::MqttWorker(
    MqttClient &client, 
    MqttSourceConfig &config, 
    std::vector<std::string> topics) :
    client_(client), config_(config), topics_(topics)
{}

bool MqttWorker::start()
{
    if(!running_){
       worker_ = std::thread(&MqttWorker::process, this); 
       return true;
    }
    return false;
}
