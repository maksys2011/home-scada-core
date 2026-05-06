#pragma once
#include <mutex>
#include <thread>
#include <atomic>
#include <chrono>
#include <unordered_map>
#include <string>
#include <vector>
#include <condition_variable>
#include <optional>
#include "ModbusClient.hpp"
#include "Enum.hpp"
#include "ModbusTransport.hpp"
#include "DataPoint.hpp"

struct ModbusReadPoint
{
    int slaveId;
    ModbusRegisterType regType;
    int startAddress;
    int count = 1;
};

class PlcWorker
{
public:
    PlcWorker(ModbusClient& client, 
        std::vector<ModbusReadPoint> readPoints);

    ~PlcWorker() noexcept;

    void start();
    void stop();
    std::optional<DataPoint> getDataPoint(int key) const;

private:
    void process();
    void readCycle();

    ModbusClient& client_;
    std::thread worker_;
    mutable std::mutex mtx_;
    std::atomic_bool running_ {false};
    std::condition_variable cv_;
    std::unordered_map<int, DataPoint> data_;
    std::vector<ModbusReadPoint> readPoints_;
    std::chrono::milliseconds pollInterval_ {200};
};
