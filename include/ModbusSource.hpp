#pragma once
#include <string>
#include <modbus/modbus.h>
#include "Source.hpp"
#include "ModbusSourceConfig.hpp"
#include "ModbusClient.hpp"
#include "PlcWorker.hpp"

class ModbusSource : public Source
{
public:    
    ModbusSource(const ModbusSourceConfig& config, 
        ModbusClient& client,
        PlcWorker& plc);
    ~ModbusSource() override;

    bool connect();
    void disconnect();
    double readValue() override;
    void writeValue(double value);
    void print() override;

private:
    ModbusSourceConfig config_;
    ModbusClient& client_;
    PlcWorker& plc_;
};