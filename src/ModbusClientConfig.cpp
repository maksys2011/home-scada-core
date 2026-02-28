#include "ModbusClientConfig.hpp"
#include <fstream>
#include <iostream>
#include "utils.hpp"
using json = nlohmann::json;

ModbusClientConfig::ModbusClientConfig(
    const std::string& nameClient, 
    const std::string& ip, 
    int port, 
    int slaveId) : nameClient_(nameClient), ip_(ip), port_(port), slaveId_(slaveId)
{}

void ModbusClientConfig::fromJson(const std::filesystem::path &path)
{
    std::ifstream file = scada::utils::create_json_ifstream(path);
    json j;
    file >> j;
    fromJson(j);
}

void ModbusClientConfig::fromJson(const json &j)
{
    auto new_nameClient = scada::utils::check_the_key<std::string>(j, "name");
    auto new_ip = scada::utils::check_the_key<std::string>(j,"ip");
    auto new_port = scada::utils::check_the_key<int>(j,"port");
    auto new_slaveId = scada::utils::check_the_key<int>(j,"slave_Id");

    validate(new_nameClient, new_ip, new_port, new_slaveId);

    nameClient_ = std::move(new_nameClient);
    ip_ = std::move(new_ip);
    port_ = new_port;
    slaveId_ = new_slaveId;
}

void ModbusClientConfig::testPrint() const
{
    std::cout << "Test print modbusClient: \n";
    std::cout << "Name client= " << nameClient_ << std::endl;
    std::cout << "ipv4= " << ip_ << std::endl;
    std::cout << "port= " << port_ << std::endl;
    std::cout << "slaveId= " << slaveId_ << std::endl;  
}

void ModbusClientConfig::validate(
    const std::string &name, 
    const std::string &ip, 
    const int port, 
    const int slaveId) const 
{
    if(name.empty()){
        throw std::runtime_error(
            name + "client name cannot be empty");
    }
    scada::utils::validateIpv4(ip, name);
    scada::utils::validatePort(port, name);
    scada::utils::validateSlaveId(slaveId, name);
}
