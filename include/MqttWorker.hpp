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
#include "MqttSourceConfig.hpp"
#include "MqttClient.hpp"

struct DataPoints
{
    double value = 0.0;
    std::chrono::system_clock::time_point timestamp;
};

class MqttWorker
{
public:
    MqttWorker(const MqttClient& client,
                MqttSourceConfig& config,
                std::vector<std::string> topics);
    
    bool start();
    void stop();
    std::optional<DataPoints> getDataPoints(std::string topic);

private:
    void process();
    void readTopic();

    MqttClient& client_;
    MqttSourceConfig& config_;
    std::mutex mtx_;
    mutable std::thread worker_;
    std::condition_variable cv_;
    std::atomic_bool running_;
    std::vector<std::string> topics_;
    std::unordered_map<std::string, DataPoints> data_;
};