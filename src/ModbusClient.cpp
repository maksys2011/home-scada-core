#include "ModbusClient.hpp"
#include <iostream>
#include <errno.h>

ModbusClient::ModbusClient(const ModbusClientConfig& config)
    :
    config_(config)
{}

ModbusClient::~ModbusClient()
{
    disconnect();
}

bool ModbusClient::connect()
{
    const auto& ip = config_.getIp();
    const auto& port = config_.getPort();
    const auto& slaveId = config_.getSlaveId();

    if(connected_) return true;

    ctx_ = modbus_new_tcp(ip.c_str(), port);

    if(!ctx_){
        std::cerr << "[ModbusClient] modbus_new_tcp failed (ip= "
        << ip << ", port=  << " << port << "\n";
        connected_ = false;
        return false;
    }
    
    if(modbus_set_slave(ctx_, slaveId) == -1){
        std::cerr << "[ModbusClient] modbus_set_slave failed: "
        << modbus_strerror(errno) << "\n";
        modbus_free(ctx_);
        ctx_ = nullptr;
        connected_ = false;
        return false;
    } 
    

    if(modbus_connect(ctx_) == -1){
        std::cerr << "[ModbusClient] connection failed: "
        << modbus_strerror(errno) << "\n";
        modbus_free(ctx_);
        ctx_ = nullptr;
        connected_ = false;
        return false;
    }

    connected_ = true;
    std::cout << "[ModbusClient] connected\n";
    
    return true;
}

bool ModbusClient::connected() const
{
    return connected_;
}

void ModbusClient::disconnect()
{
    if(ctx_){
        modbus_close(ctx_);
        modbus_free(ctx_);
        ctx_ = nullptr;
    }
    connected_ = false;
    
    std::cout << "[ModbusClient] Disconnected\n";
}

uint16_t ModbusClient::readHolding(int address)
{

    if(!connected_ && !connect()){
        throw std::runtime_error("[ModbusClient] not connected");
    }

    uint16_t reg = 0;
    int rc = modbus_read_registers(ctx_, address, 1, &reg);
    
    if(rc == -1){
        throw std::runtime_error (
            std::string("[ModbusClient] modbus read registers failed : ") +
            modbus_strerror(errno)
        );
    }

    return reg;
}

uint16_t ModbusClient::readInput(int address)
{
    if(!connected_ && !connect()){
        throw std::runtime_error("[ModbusClient] not connected");
    }
    
    uint16_t reg = 0;
    int rc = modbus_read_input_registers(ctx_, address, 1, &reg);
    
    if(rc == -1){
        throw std::runtime_error ( 
            std::string("[ModbusClient] modbus read input registers failed : ") +
            modbus_strerror(errno)
        );      
    }

    return reg;
}

bool ModbusClient::readCoil(int address)
{
    if(!connected_ && !connect()){
        throw std::runtime_error("[ModbusClient] not connected");
    }

    uint8_t reg = 0;
    int rc = modbus_read_bits(ctx_, address, 1, &reg);

    if(rc == -1){
        throw std::runtime_error ( 
            std::string("[ModbusClient] modbus read bits registers failed : ") +
            modbus_strerror(errno)
        );      
    }

    return reg != 0;
}

uint16_t ModbusClient::readDiscrete(int address)
{
    if(!connected_ && !connect()){
        throw std::runtime_error("[ModbusClient] not connected");
    }

    uint8_t reg = 0;
    int rc = modbus_read_input_bits(ctx_, address, 1, &reg);

        if(rc == -1){
        throw std::runtime_error ( 
            std::string("[ModbusClient] modbus read input bits registers failed : ") +
            modbus_strerror(errno)
        );      
    }

    return reg;
}

void ModbusClient::writeRegister(int address, uint16_t value)
{
    if(!connected_ && !connect()){
        throw std::runtime_error("[ModbusClient] not connected");
    }

    int rc = modbus_write_register(ctx_, address, value);

    if(rc == -1){
        throw std::runtime_error(
            std::string("[ModbusClient] writeRegister failed: ") +
            modbus_strerror(errno)
        );
    }

}

void ModbusClient::writeCoil(int address, bool value)
{
    if(!connected_ && !connect()){
        throw std::runtime_error("[ModbusClient] not connected");
    }

    int rc = modbus_write_bit(ctx_, address, value);

     if(rc == -1){
        throw std::runtime_error(
            std::string("[ModbusClient] writeCoil failed: ") +
            modbus_strerror(errno)
        );
    }

}
