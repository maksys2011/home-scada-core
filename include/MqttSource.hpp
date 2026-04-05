#pragma once

#include <mutex>
#include <string>
#include <mqtt/async_client.h>
#include <functional>
#include "MqttSourceConfig.hpp"
#include "Source.hpp"

class MqttSource : public Source
{
public:
    MqttSource(const MqttSourceConfig& config);
    ~MqttSource() override;

    double readValue() override;
    bool connect() override;
    void print() override;

private:
    
    MqttSourceConfig config_; 
    mqtt::async_client client_;
    double lastValue_ = 0.0;
    std::mutex mtx_;
    bool isConnected_ = false;
    bool hasValue_ = false;
};

