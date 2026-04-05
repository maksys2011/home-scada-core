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
   switch (config_.getTypeRegister())
   {
        case ModbusRegisterType::Coil:
            return static_cast<double>(
            client_.readCoil(config_.getStartAddress()));

        case ModbusRegisterType::DiscreteInput: 
            return static_cast<double>(
            client_.readDiscrete(config_.getStartAddress()));

        case ModbusRegisterType::HoldingRegister: 
            return static_cast<double>(
            client_.readHolding(config_.getStartAddress()));

        case ModbusRegisterType::InputRegister:
            return static_cast<double>(
            client_.readInput(config_.getStartAddress()));

        default: 
            throw std::runtime_error("Unsupported Modbus type");
   }
}

void ModbusSource::writeValue(double value)
{
    switch (config_.getTypeRegister())
    {
        case ModbusRegisterType::Coil:
            client_.writeCoil(config_.getStartAddress(),
            static_cast<bool>(value));
            break;
        
        case ModbusRegisterType::DiscreteInput:
            client_.writeRegister(config_.getStartAddress(),
            static_cast<uint16_t>(value));
            break;

        case ModbusRegisterType::HoldingRegister:
        case ModbusRegisterType::InputRegister:
            throw std::runtime_error("register type is read-only");

        default:
             throw std::runtime_error("Unsupported write type");
    }
}

void ModbusSource::print()
{
    std::cout << "ModbusSource: " << std::endl;
    config_.print();
}
