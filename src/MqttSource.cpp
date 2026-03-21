#include "MqttSource.hpp"

MqttSource::MqttSource(const MqttSourceConfig &config)
    :
    config_(config),
    client_(config_.getBroker(), config_.getClient())
{}

MqttSource::~MqttSource()
{
    try
    {
        if(isConnected_){
        client_.stop_consuming();
        client_.disconnect()->wait();
        }
    }
    catch(const mqtt::exception& e)
    {
        std::cerr << "MqttSource destructor disconnect error: " << e.what() << '\n';
    }   
}

double MqttSource::readValue()
{
    if(!isConnected_) {
        return lastValue_;
    }

    try
    {
        auto msg = client_.try_consume_message_for(std::chrono::milliseconds(5));
        if(msg){
            std::string payLoad = msg->to_string();

            double value = std::stod(payLoad);

            std::lock_guard<std::mutex> lock(mtx_);
            lastValue_ = value;
            hasValue_ = true;
        } 
    }
    catch(const std::exception& e)
    {
        std::cerr << "[MQTT] readValue parse/consume error: " << e.what() << '\n';
    }

    std::lock_guard<std::mutex> lock(mtx_);
    return lastValue_;
}

bool MqttSource::connect()
{
    try
    {
        client_.start_consuming();
        mqtt::connect_options connOpts;
        connOpts.set_clean_session(true);

        client_.connect(connOpts)->wait();
        client_.subscribe(
            config_.getTopic(),
            config_.getQos())->wait();

        isConnected_ = true;

        std::cout << "[MQTT] connected to broker: " << config_.getBroker()
                    << " |  topic: " << config_.getTopic() << '\n';
        return true;
    }
    catch(const mqtt::exception& e)
    {
        std::cerr << "[MQTT] connect failed " << e.what() << '\n';
        
        return false;
    }
    
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


