#include "MqttClient.hpp"
#include <iostream>

MqttClient::MqttClient(const std::string &addr, const std::string &id) :
    client_(addr, id)
{}

MqttClient::~MqttClient()
{
    try
    {
        if(isConnected_){
            client_.stop_consuming();
            client_.disconnect()->wait();
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "MqttSource destructor disconnect error: " << e.what() << '\n';
    }
}

bool MqttClient::connect(const std::vector<std::string>& topics)
{
    auto connection_options = mqtt::connect_options_builder()
        .keep_alive_interval(std::chrono::seconds(60))
        .clean_session(true)
        .finalize();
    try
    {
        client_.start_consuming();

        client_.connect(connection_options)->wait();

        for(const auto& topic : topics){
            client_.subscribe(topic, 1)->wait();
        }
        
        isConnected_ = true;
        return true;
    }
    catch(const std::exception& e)
    {
        std::cerr << "[MQTT] Connetion error: " << e.what() << '\n';
        isConnected_ = false;
        return false;
    }
}

std::optional<mqtt::const_message_ptr> MqttClient::tryConsume()
{
    auto msg = client_.try_consume_message_for(std::chrono::milliseconds(500));
    return msg;
}
