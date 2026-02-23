#pragma once
#include <string>
#include <modbus/modbus.h>
#include "Source.hpp"
#include "ModbusSourceConfig.hpp"
#include "ModbusClient.hpp"

class ModbusSource : public Source
{
public:    
    ModbusSource(const ModbusSourceConfig& config, ModbusClient& client);
    ~ModbusSource() override;

    bool connect();
    void disconnect();
    double readValue() override;
    void writeValue(double value);

private:

    ModbusSourceConfig config_;
    ModbusClient& client_;
};