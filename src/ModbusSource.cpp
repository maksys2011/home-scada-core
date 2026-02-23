#include "ModbusSource.hpp"
#include <iostream>

ModbusSource::ModbusSource(const ModbusSourceConfig& config, ModbusClient& client)
    :
    config_(std::move(config)),
    client_(client)
{}

ModbusSource::~ModbusSource()
{}

bool ModbusSource::connect()
{
    return client_.connect();
}

void ModbusSource::disconnect()
{
    client_.disconnect();
}

double ModbusSource::readValue()
{
   switch (config_.getTypeSource())
   {
        case ModbusObjectType::Coil:
            return static_cast<double>(
            client_.readCoil(config_.getStartAddress()));

        case ModbusObjectType::DiscreteInput: 
            return static_cast<double>(
            client_.readDiscrete(config_.getStartAddress()));

        case ModbusObjectType::HoldingRegister: 
            return static_cast<double>(
            client_.readHolding(config_.getStartAddress()));

        case ModbusObjectType::InputRegister: 
            return static_cast<double>(
            client_.readInput(config_.getStartAddress()));

        default: 
            throw std::runtime_error("Unsupported Modbus type");
   }
}

void ModbusSource::writeValue(double value)
{
    switch (config_.getTypeSource())
    {
        case ModbusObjectType::Coil:
            client_.writeCoil(config_.getStartAddress(),
            static_cast<bool>(value));
            break;
        
        case ModbusObjectType::HoldingRegister:
            client_.writeRegister(config_.getStartAddress(),
            static_cast<uint16_t>(value));
            break;

        case ModbusObjectType::DiscreteInput:
        case ModbusObjectType::InputRegister:
            throw std::runtime_error("register type is read-only");

        default:
             throw std::runtime_error("Unsupported write type");
    }
}

