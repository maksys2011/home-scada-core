#pragma once
#include <string>
#include "ITransport.hpp"
#include "MqttCommandPublisher.hpp"
#include "MqttClient.hpp"

class MqttTransport : public ITransport
{
private:
    MqttClient& client_;

    public:
    MqttTransport() = default;
    MqttTransport(MqttClient& client);
    bool send(const std::string& target, const TransportValue& val) override;
};