#include "MqttCommandPublisher.hpp"

MqttCommandPublisher::MqttCommandPublisher(
    const std::string &broker, 
    const std::string &clientId):
    client_(broker, clientId),
    isConnected_(false)
{}

MqttCommandPublisher::~MqttCommandPublisher()
{
    disconnect();
}

bool MqttCommandPublisher::connect()
{
    try
    {
        mqtt::connect_options connOpts;
        connOpts.set_clean_session(true);

        client_.connect(connOpts)->wait();
        isConnected_ = true;

        std::cout << "[MQTT CMD] Connected\n";
        return true;
    }
    catch(const std::exception& e)
    {
        std::cerr << "[MQTT CMD] Connect error:  "<< e.what() << '\n';
        isConnected_ = false;
        return false;
    }
}

void MqttCommandPublisher::disconnect()
{
    if(!isConnected_) return;

    try
    {
        client_.disconnect()->wait();
        isConnected_ = false;
        std::cout << "[MQTT CMD] Disconnected\n";
    }
    catch(const std::exception& e)
    {
        std::cerr << "[MQTT CMD] Disconnected error: "<< e.what() << '\n';
    }
    
}

bool MqttCommandPublisher::publishCommand(const std::string &topic, const std::string &payLoad)
{
    if(!isConnected_) {
        std::cerr << "[MQTT CMD] Not connected, skip publish\n";
        return;
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
    }
}

void MqttCommandPublisher::publishOn(const std::string &topic)
{
    publishCommand(topic, "ON");
}

void MqttCommandPublisher::publishOff(const std::string &topic)
{
    publishCommand(topic, "OFF");
}

bool MqttCommandPublisher::isConnected() const 
{
    return isConnected_;
}


