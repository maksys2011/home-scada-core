#pragma once

#include <string>
#include <mqtt/async_client.h>

class MqttCommandPublisher
{
public:
    MqttCommandPublisher(const std::string& broker, 
                        const std::string& clientId);
    ~MqttCommandPublisher();
    bool connect();
    void disconnect();
    bool isConnected() const;

    bool publishCommand(const std::string& topic,
                        const std::string& payLoad);
    void publishOn(const std::string& topic);
    void publishOff(const std::string& topic);

private:
    mqtt::async_client client_;
    bool isConnected_ = true;
};