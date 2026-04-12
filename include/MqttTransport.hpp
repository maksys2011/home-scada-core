#pragma once
#include <string>
#include "ITransport.hpp"
#include "MqttCommandPublisher.hpp"

class MqttTransport : public ITransport
{
private:
    MqttCommandPublisher client_;
public:
    bool send(const std::string& target, const TransportValue& val) override;
};