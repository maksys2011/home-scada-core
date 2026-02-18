#include <fstream>
#include <iostream>
#include "ModbusSourceConfig.hpp"
#include "utils.hpp"

ModbusSourceConfig::ModbusSourceConfig(
    const std::string& ip, 
    int port, 
    int slave_Id, 
    int startAddress, 
    const std::string& typeNameSource)
    :
    ip_(ip),
    port_(port),
    slave_Id_(slave_Id),
    startAddress_(startAddress),
    typeSource_(ParseModbusObjectType(typeNameSource))
{}

void ModbusSourceConfig::fromJson(const std::filesystem::path &pathFile)
{
    std::ifstream file(pathFile);
    if(!file.is_open()){
        throw std::runtime_error(
            "cannot open modbusSourceConfig file: " + pathFile.string());
    }
    json j;
    file >> j;
    fromJson(j);
}

void ModbusSourceConfig::fromJson(const json &j)
{ 
    ip_ = scada::utils::check_the_key<std::string>(j, "ip");
    port_ = scada::utils::check_the_key<int>(j, "port");
    slave_Id_ = scada::utils::check_the_key<int>(j, "slave_Id");
    startAddress_ = scada::utils::check_the_key<int>(j, "startAddress");
    typeSource_ = ParseModbusObjectType(scada::utils::check_the_key<std::string>(j, "typeSource"));
}

void ModbusSourceConfig::testPrintInfo() const
{
    std::cout << "Creating Modbus source configurations\n";
    std::cout << "ip= " << ip_ << "\n";
    std::cout << "slave id= " <<  slave_Id_ << "\n";
    std::cout << "startAddress=" << startAddress_ << "\n";
    std::cout << "typeSource=" << ModbusObjectTypeToString(typeSource_) << "\n";
}
