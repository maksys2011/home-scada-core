#pragma once
#include <mutex>
#include <condition_variable>
#include <thread>
#include <string>
#include <vector>
#include <atomic>
#include <chrono>
#include <unordered_map>
#include <optional>
#include <mqtt/async_client.h>
#include "MqttSourceConfig.hpp"
#include "MqttClient.hpp"
#include "DataPoint.hpp"

class MqttWorker
{
public:
    MqttWorker(MqttClient& client);
    
    MqttWorker(const MqttWorker&) = delete;
    MqttWorker& operator=(const MqttWorker&) = delete;

    MqttWorker(MqttWorker&&) = delete;
    MqttWorker& operator=(MqttWorker&&) = delete;

    ~MqttWorker() noexcept;

    bool start();
    void stop();
    std::optional<DataPoint> getDataPoints(const std::string& topic);

private:
    void process();

    MqttClient& client_;
    std::mutex mtx_;
    mutable std::thread worker_;
    std::atomic_bool running_{false};
    std::unordered_map<std::string, DataPoint> cache_;
};