#include "MqttSource.hpp"

MqttSource::MqttSource(
    MqttSourceConfig &config, 
    MqttWorker &worker) :
    config_(config), worker_(worker)
{}

MqttSource::~MqttSource()
{}

double MqttSource::readValue()
{
    auto new_value = worker_.getDataPoints(config_.getTopic());

    if(new_value){
        return new_value->value;
    }

    return 0.0;
}

bool MqttSource::connect()
{
    return true;
}

void MqttSource::print()
{
    std::cout << "MqttSource:\n"
              << "  sourceId: " << config_.getSourceId() << '\n'
              << "  name: " << config_.getName() << '\n'
              << "  broker: " << config_.getBroker() << '\n'
              << "  clientId: " << config_.getClient() << '\n'
              << "  topic: " << config_.getTopic() << '\n'
              << "  qos: " << config_.getQos() << '\n';
}


