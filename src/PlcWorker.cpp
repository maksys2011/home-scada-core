#include "PlcWorker.hpp"

PlcWorker::PlcWorker(ModbusClient &client, 
    std::vector<ModbusReadPoint> readPoints)
    : client_(client), 
    readPoints_(std::move(readPoints))
{}

PlcWorker::~PlcWorker() noexcept
{
    stop();
}

void PlcWorker::start()
{
    if(running_) {
        return;
    }
    running_ = true;
    worker_ = std::thread(&PlcWorker::process, this);
}

void PlcWorker::stop()
{
    if(!running_){
        return;
    }
    running_ = false;
    cv_.notify_all();

    if(worker_.joinable()){
        worker_.join();
    }
}

std::optional<DataPoint> PlcWorker::getDataPoint(const std::string &key) const
{
    std::lock_guard<std::mutex> lock(mtx_);

    auto it = data_.find(key);

    if(it == data_.end()){
        return std::nullopt; 
    }
        
    return it->second;    
}


void PlcWorker::process()
{
    while(running_){

        readCycle();

        std::unique_lock<std::mutex> lock(mtx_);

        cv_.wait_for(lock, pollInterval_, [this](){
            return !running_;
        });

    }
}

void PlcWorker::readCycle()
{
    for(const auto& it : readPoints_){

        if(it.count != 1){
            continue;
        }

        auto reg = it.regType;
        int address = it.startAddress;
        double value {0.0};
        bool success = false;

        if(reg == ModbusRegisterType::Coil){
            value = client_.readCoil(address);
            success = true;
        }else if(reg == ModbusRegisterType::DiscreteInput){
            value = client_.readDiscrete(address);
            success = true;
        }else if(reg == ModbusRegisterType::InputRegister){
            value = client_.readInput(address);
            success = true;
        }else if(reg == ModbusRegisterType::HoldingRegister){
            value = client_.readHolding(address);
            success = true;
        }
        
        if(!success){
            continue;
        }

        std::lock_guard<std::mutex> lock(mtx_);

        DataPoint data;
        data.timestamp = std::chrono::system_clock::now();
        data.value = value;
        data_[it.key] = data;
    }
}

