#include "ModbusTransport.hpp"
#include <iostream>

ModbusTransport::ModbusTransport(ModbusClient &client) : client_(client) {}

bool ModbusTransport::send(const std::string &target, const TransportValue &val)
{
    try{

        int startAddress = std::stoi(target);

        if(const int* cmd = std::get_if<int>(&val)){
            client_.writeRegister(startAddress, static_cast<uint16_t>(*cmd));
            return true;
        }

        if(const bool* cmd = std::get_if<bool>(&val)){
            client_.writeCoil(startAddress, static_cast<uint16_t>(*cmd));
            return true;
        }

        if(const double* cmd = std::get_if<double>(&val)){
            // client_.writeFloat(startAddress, static_cast<float>(*cmd));
            return true;
        }

    }catch (const std::invalid_argument& e ){
        std::cerr << "Modbus Error: Invalid address string: " 
            << target << e.what() << std::endl;
    }catch (const std::out_of_range& e ){
        std::cerr << "Modbus Error: Address out of range: " 
            << target << e.what() << std::endl;
    }
    return false;
}