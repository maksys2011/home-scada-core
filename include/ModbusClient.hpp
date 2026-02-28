#pragma once 
#include <string>
#include <modbus/modbus.h>
#include "ModbusClientConfig.hpp"

class ModbusClient
{
public:
    ModbusClient(const ModbusClientConfig& config);
    ~ModbusClient();

    ModbusClient(const ModbusClient&) = delete;
    ModbusClient& operator=(const ModbusClient& ) = delete;

    bool connect();
    bool connected() const ;
    void disconnect();

    bool readCoil(int address);
    uint16_t readDiscrete(int address);
    uint16_t readHolding(int address);
    uint16_t readInput(int address);

    void writeRegister(int address, uint16_t value);
    void writeCoil(int address, bool value);

private:
    ModbusClientConfig config_;
    bool connected_ = false;
    modbus_t* ctx_ = nullptr;
};