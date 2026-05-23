#include "MqttClient.hpp"
#include <iostream>

MqttClient::MqttClient(const std::string &addr, const std::string &id) :
    client_(addr, id)
{}

MqttClient::~MqttClient()
{

    disconnect();

}

bool MqttClient::connect(const std::vector<std::string>& topics)
{
    std::lock_guard<std::mutex> lock(mqtt_mtx_);

    auto connection_options = mqtt::connect_options_builder()
        .keep_alive_interval(std::chrono::seconds(60))
        .clean_session(true)
        .finalize();
    try
    {
        client_.connect(connection_options)->wait();

        for(const auto& topic : topics){
            client_.subscribe(topic, 1)->wait();
        }

        client_.start_consuming();
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

void MqttClient::disconnect()
{
    std::lock_guard<std::mutex> lock(mqtt_mtx_);

    if(!isConnected_) return;

    try
    {
        client_.stop_consuming();
        client_.disconnect()->wait();
        isConnected_ = false;
        std::cout << "[MQTT CMD] Disconnected\n";
    }
    catch(const std::exception& e)
    {
        std::cerr << "[MQTT CMD] Disconnected error: "<< e.what() << '\n';
    }
}

std::optional<mqtt::const_message_ptr> MqttClient::tryConsume()
{
    std::lock_guard<std::mutex> lock(mqtt_mtx_);

    auto msg = client_.try_consume_message_for(std::chrono::milliseconds(50));
    
    return msg;
}

bool MqttClient::publishCommand(const std::string &topic, const std::string &payLoad)
{
    std::lock_guard<std::mutex> lock(mqtt_mtx_);

    if(!isConnected_) {
        std::cerr << "[MQTT CMD] Not connected, skip publish\n";
        return false;
    }

    try
    {
        client_.publish(topic, payLoad.c_str(), payLoad.size(), 1, false)->wait();

        std::cout << "[MQTT CMD] Published: " << topic 
                    << " -> " << payLoad << '\n';
    }
    catch(const std::exception& e)
    {
        std::cerr << "[MQTT CMD] Publish error: " << e.what() << '\n';
        return false;
    }
    
    return true;
}

void MqttClient::publishOn(const std::string &topic)
{
    publishCommand(topic, "ON");
}

void MqttClient::publishOff(const std::string &topic)
{
    publishCommand(topic, "OFF");
}
