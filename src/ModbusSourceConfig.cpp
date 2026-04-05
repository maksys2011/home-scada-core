#include <fstream>
#include <iostream>
#include <algorithm>
#include "ModbusSourceConfig.hpp"
#include "utils.hpp"

ModbusSourceConfig::ModbusSourceConfig(
    const std::string& clientId,
    const std::string& sourceId,
    const std::string& ip, 
    int port, 
    int slave_Id, 
    int startAddress, 
    const std::string& register_type,
    const std::string& source_type)
    :
    client_id_(clientId),
    source_id_(sourceId),
    ip_(ip),
    port_(port),
    slave_Id_(slave_Id),
    startAddress_(startAddress),
    register_type_(ParseModbusRegisterType(register_type)),
    source_type_(ParceSourceType(source_type))    
{}

void ModbusSourceConfig::fromJson(const std::filesystem::path &pathFile)
{
    std::ifstream file = scada::utils::create_json_ifstream(pathFile);
    json j;
    file >> j;
    fromJson(j);
}

void ModbusSourceConfig::fromJson(const json &j)
{ 
    auto new_clientId = scada::utils::check_the_key<std::string>(j, "client_id");
    auto new_sourceId = scada::utils::check_the_key<std::string>(j, "source_id");
    auto new_ip = scada::utils::check_the_key<std::string>(j, "ip"); 
    auto new_port = scada::utils::check_the_key<int>(j, "port");
    auto new_slave_Id = scada::utils::check_the_key<int>(j, "slave_id");
    auto new_startAddress = scada::utils::check_the_key<int>(j, "startAddress");
    auto new_register_type = scada::utils::check_the_key<std::string>(j, "register_type");
    auto new_source_type = scada::utils::check_the_key<std::string>(j,"type_source");

    validate(new_clientId, 
        new_sourceId, 
        new_ip, 
        new_port, 
        new_slave_Id, 
        new_startAddress, 
        new_register_type
    );

    client_id_ = std::move(new_clientId);
    source_id_ = std::move(new_sourceId);
    ip_ = std::move(new_ip);
    port_ = new_port;
    slave_Id_ =new_slave_Id;
    startAddress_ = new_startAddress;
    register_type_ = ParseModbusRegisterType(new_register_type);
    source_type_ = ParceSourceType(new_source_type);
}

void ModbusSourceConfig::print()
{
    std::cout << "Creating Modbus source configurations" << std::endl;
    std::cout << "client id= " << client_id_ << std::endl;
    std::cout << "source id= " << source_id_ << std::endl;
    std::cout << "ip= " << ip_ << std::endl;
    std::cout << "port= " << port_ << std::endl; 
    std::cout << "slave id= " <<  slave_Id_ << std::endl;
    std::cout << "startAddress= " << startAddress_ << std::endl;
    std::cout << "register type= " << ModbusRegisterTypeToString(register_type_) << std::endl;
    std::cout << "source type= " << ParseSourceTypeToString(source_type_) << std::endl;
}
 
void ModbusSourceConfig::validateStartAddress(const int startAddress) const
{
    if(startAddress < 0){
        throw std::runtime_error(
            "ModbusSourceConfig: start address out of range (min: 0) " +
            std::to_string(startAddress)
        );
    }
}

void ModbusSourceConfig::validateModbusRegisterType(const std::string& registerType) const
{
    if(validSourceTypes.count(registerType) == 0){
        throw std::runtime_error(
            "ModbusSourceConfig: unsupported source type -> " + registerType
        );
    }
}

void ModbusSourceConfig::validate(
    const std::string& clientId,
    const std::string& sourceId, 
    const std::string& ip, 
    const int port, 
    const int slaveId, 
    const int startAddress, 
    const std::string& register_type
) const

{
    std::string name = "ModbusSource";
    scada::utils::validateId(clientId, name);
    scada::utils::validateId(sourceId, name);
    scada::utils::validateIpv4(ip, name);
    scada::utils::validatePort(port, name);
    scada::utils::validateSlaveId(slaveId, name);
    validateStartAddress(startAddress);
    validateModbusRegisterType(register_type);
}
