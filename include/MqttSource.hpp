#pragma once
#include <mutex>
#include <string>
#include <mqtt/async_client.h>
#include <functional>
#include "MqttSourceConfig.hpp"
#include "Source.hpp"
#include "MqttWorker.hpp"
#include "DataPoint.hpp"

class MqttSource : public Source
{
public:
    MqttSource(MqttSourceConfig& config,
                MqttWorker& worker);
    ~MqttSource() override;

    double readValue() override;
    bool connect() override;
    void print() override;

private:
    
    MqttSourceConfig& config_; 
    MqttWorker& worker_;
    double lastValue_ = 0.0;
    std::mutex mtx_;
    bool isConnected_ = false;
    bool hasValue_ = false;
};

