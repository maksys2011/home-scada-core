#pragma once
#include <mqtt/async_client.h>
#include <vector>
#include <string>
#include <optional>
#include <mutex>
#include <atomic>

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
    MqttClient(const MqttClient&) = delete;
    MqttClient& operator=(const MqttClient&) = delete; 
    
    
    ~MqttClient();

    bool connect(const std::vector<std::string>& topics);
    void disconnect();
    bool connection_check() const  {return isConnected_; };
    
    std::optional<mqtt::const_message_ptr> tryConsume();

    bool publishCommand(const std::string &topic, const std::string &payLoad);
    void publishOn(const std::string& topic);
    void publishOff(const std::string& topic);

private:
    mqtt::async_client client_;
    std::atomic_bool isConnected_ = false;
    mutable std::mutex mqtt_mtx_;
};