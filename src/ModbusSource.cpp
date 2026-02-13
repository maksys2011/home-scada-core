#include "ModbusSource.hpp"
#include <iostream>

ModbusSource::ModbusSource(
    const std::string &ip, 
    int port, 
    int slaveId, 
    int startAddress)
    :
    ip_(ip),
    port_(port),
    slaveId_(slaveId),
    startAddress_(startAddress)
{
    std::cout << "[ModbusSource]: created for" << "\n"
                << "ip= " <<  ip_ << "\n"
                << "port= " << port_ << "\n"
                << "slaveId= " << slaveId_ << "\n"
                << "startAddress= " << startAddress_ << "\n";
}

ModbusSource::~ModbusSource()
{
    disconnect();
}

bool ModbusSource::connect()
{
    if(connected_) return true;

    ctx_ = modbus_new_tcp(ip_.c_str(), port_);
    if(!ctx_){
        std::cerr << "[ModbusSource] failed to create context\n";
        return false;
    }

    modbus_set_slave(ctx_, slaveId_);

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
    int rc = modbus_read_registers(ctx_, startAddress_, 1, &reg);

    if(rc == -1){
           std::cerr << "[ModbusSource] Read failed: " 
                  << modbus_strerror(errno) << "\n";
        return 0.0;
    }
     
    return static_cast<double>(reg);
}
