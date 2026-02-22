#pragma once 
#include <string>
#include <modbus/modbus.h>

class ModbusClient
{
public:
    ModbusClient(const std::string& ip, int port, int slaveId);
    ~ModbusClient();

    ModbusClient(const ModbusClient&) = delete;
    ModbusClient& operator=(const ModbusClient& ) = delete;

    bool connect();
    bool connected() const ;
    void disconnect();

    uint16_t readHolding(int address);
    uint16_t readInput(int address);
    bool readCoil(int address);

    void writeRegister(int address, uint16_t value);
    void writeCoil(int address, bool value);

private:
    std::string ip_;
    int port_;
    int slaveId_;
    bool connected_ = false;
    modbus_t* ctx_ = nullptr;
};