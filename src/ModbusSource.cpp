#include "ModbusSource.hpp"
#include <iostream>

ModbusSource::ModbusSource(ModbusSourceConfig config)
    : 
    config_(std::move(config))
{}

ModbusSource::~ModbusSource()
{
    disconnect();
}

bool ModbusSource::connect()
{
    if(connected_) return true;

    ctx_ = modbus_new_tcp(config_.getIp().c_str(), config_.getPort());
    if(!ctx_){
        std::cerr << "[ModbusSource] failed to create context\n";
        return false;
    }

    modbus_set_slave(ctx_, config_.getSlaveId());

    if(modbus_connect(ctx_) == -1){
        std::cerr << "[ModbusSource] connection failed: "
                  << modbus_strerror(errno) << "\n";
        modbus_free(ctx_);
        ctx_ = nullptr;
        return false;
    }

    connected_ = true;
    std::cout << "[ModbusSource] connected\n";
    
    return true;
}

void ModbusSource::disconnect()
{
    if(ctx_){
        modbus_close(ctx_);
        modbus_free(ctx_);
        ctx_ = nullptr;
    }
    connected_ = false;
    std::cout << "[ModbusSource] Disconnected";
}

double ModbusSource::readValue()
{

    if(!connected_ || !ctx_){
        return 0.0;
    }

    uint16_t reg;
    int rc = modbus_read_registers(ctx_, config_.getStartAddress(), 1, &reg);

    if(rc == -1){
           std::cerr << "[ModbusSource] Read failed: " 
                  << modbus_strerror(errno) << "\n";
        return 0.0;
    }
     
    return static_cast<double>(reg);
}

void ModbusSource::testPrint()
{
    std::cout << "[ModbusSource]: created for" << "\n"
            << "ip= " <<  config_.getIp() <<"\n"
            << "port= " << config_.getPort() << "\n"
            << "slaveId= " << config_.getSlaveId() << "\n"
            << "startAddress= " << config_.getStartAddress() << "\n";
}
