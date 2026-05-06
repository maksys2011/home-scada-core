#pragma once
#include <mqtt/async_client.h>
#include <vector>
#include <string>
#include <optional>

/**
 * MQTT transport client.
 * Отвечает за:
 * - connection lifecycle
 * - subscriptions
 * - consuming MQTT messages
 */

class MqttClient
{
public:
    MqttClient(const std::string& addr,
                const std::string& id);
    ~MqttClient();

    bool connect(const std::vector<std::string>& topics);
    bool connected() const  {return isConnected_; };
    std::optional<mqtt::const_message_ptr> tryConsume();

private:
    mqtt::async_client client_;
    bool isConnected_ = false;
};