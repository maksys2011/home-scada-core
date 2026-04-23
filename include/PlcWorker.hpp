#pragma once
#include <mutex>
#include <thread>
#include <atomic>
#include <chrono>
#include <unordered_map>
#include <string>
#include <vector>
#include <condition_variable>
#include "ModbusClient.hpp"
#include "Enum.hpp"
#include "ModbusTransport.hpp"

struct DataPoint
{
    double value = 0.0;
    std::chrono::system_clock::time_point timestamp;
};

struct ModbusReadPoint
{
    std::string key;
    int slaveId;
    ModbusRegisterType regType;
    int startAddress;
    int count = 1;
};

struct ModbusWritePoint
{
    std::string key;
    int slaveId;
    ModbusRegisterType regType;
    int startAddress;
    int value;
};

class PlcWorker
{
public:
    PlcWorker(ModbusClient& client, 
        std::vector<ModbusReadPoint> readPoints);

    ~PlcWorker() noexcept;

    void start();
    void stop();
    void setWtite();

private:
    void process();
    void readCycle();

    ModbusClient& client_;
    std::thread worker_;
    mutable std::mutex mtx_;
    std::atomic_bool running_ {false};
    std::condition_variable cv_;
    std::unordered_map<std::string, DataPoint> data_;
    std::vector<ModbusReadPoint> readPoints_;
    std::vector<ModbusWritePoint> pendingWrites_;
    std::chrono::milliseconds pollInterval_ {200};
};
