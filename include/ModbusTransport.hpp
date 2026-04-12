#pragma once
#include <string>
#include <variant>
#include "ITransport.hpp"
#include "ModbusClient.hpp"

class ModbusTransport : public ITransport
{
public:
    ModbusTransport(ModbusClient& client);
    bool send(const std::string& target, const TransportValue& val) override;
private:
    ModbusClient& client_;
};