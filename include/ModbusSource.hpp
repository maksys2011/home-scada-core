#pragma once
#include <string>
#include <modbus/modbus.h>
#include "Source.hpp"
#include "ModbusSourceConfig.hpp"

class ModbusSource : public Source
{
public:    
    ModbusSource(ModbusSourceConfig config);
    ~ModbusSource() override;

    bool connect();
    void disconnect();
    double readValue() override;
    void testPrint();

private:
    std::string ip_;
    int port_ = 1502;
    int slaveId_ = 1;
    int startAddress_ = 0;

    bool connected_ = false;
    modbus_t* ctx_ = nullptr;

    ModbusSourceConfig config_;
};