#include <fstream>
#include <iostream>
#include <algorithm>
#include "ModbusSourceConfig.hpp"
#include "utils.hpp"

ModbusSourceConfig::ModbusSourceConfig(
    const std::string& id,
    const std::string& ip, 
    int port, 
    int slave_Id, 
    int startAddress, 
    const std::string& typeNameSource)
    :
    id_(id),
    ip_(ip),
    port_(port),
    slave_Id_(slave_Id),
    startAddress_(startAddress),
    typeSource_(ParseModbusObjectType(typeNameSource))
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
    auto new_id = scada::utils::check_the_key<std::string>(j, "id");
    auto new_ip = scada::utils::check_the_key<std::string>(j, "ip"); 
    auto new_port = scada::utils::check_the_key<int>(j, "port");
    auto new_slave_Id = scada::utils::check_the_key<int>(j, "slave_Id");
    auto new_startAddress = scada::utils::check_the_key<int>(j, "startAddress");
    auto new_typeSource = scada::utils::check_the_key<std::string>(j, "typeSource");

    validate(new_id, new_ip, new_port, new_slave_Id, new_startAddress, new_typeSource);

    id_ = new_id;
    ip_ = new_ip;
    port_ = new_port;
    slave_Id_ =new_slave_Id;
    startAddress_ = new_startAddress;
    typeSource_ = ParseModbusObjectType(new_typeSource);
}

void ModbusSourceConfig::testPrintInfo() const
{
    std::cout << "Creating Modbus source configurations\n";
    std::cout << "id= " << id_ << "\n";
    std::cout << "ip= " << ip_ << "\n";
    std::cout << "port= " << port_ << "\n"; 
    std::cout << "slave id= " <<  slave_Id_ << "\n";
    std::cout << "startAddress=" << startAddress_ << "\n";
    std::cout << "typeSource=" << ModbusObjectTypeToString(typeSource_) << "\n";
}

void ModbusSourceConfig::validateId(const std::string &id) const
{
   if(id.empty()){
    throw std::runtime_error(
        "ModbusSourceConfig: id cannot be empty"
    );
   }
   bool result = std::all_of(id.begin(), id.end(),
    [](unsigned char ch){
        return std::isspace(ch);
    });

    if(result){
        throw std::runtime_error(
            "ID cannot contain only whitespace"
        );
    }
}

void ModbusSourceConfig::validateIpv4(const std::string &ip) const
{
    if(ip.empty()){
        throw std::runtime_error("ModbusSourceConfig: ip address cannot be empty");
    }

    std::stringstream str(ip);
    std::string segment;
    int count = 0;

    while(std::getline(str, segment, '.')){
            
        if(segment.empty() || segment.length() > 3){
           throw std::runtime_error("ModbusSourceConfig: ip segment cannot exceed 3 characters "
            + segment + " -> " + ip); 
        }
        
        for(char ch : segment){
            if(!std::isdigit(ch)){
                throw std::runtime_error(
                    std::string("ModbusSourceConfig: ip address can only contain digits (0-9) " 
                        + segment + " -> " + ip));
            }
        }
        
        int value = std::stoi(segment);
        
        if(value >= 0 && value <= 255){
            count++;
        }else{
            throw std::runtime_error(
                std::string("ModbusSourceConfig: ip segment value must be between 0 and 255 " 
                    + segment + " -> " + ip));
        }
    }

    if(count < 4 || count > 4){
            throw std::runtime_error("ModbusSourceConfig: ip address must contain 4 segments  -> " + ip);
        }
    
}

void ModbusSourceConfig::validatePort(const int port) const
{
    if(port < 0 || port > 65535){
        throw std::runtime_error(
            "ModbusSourceConfig: port must be in range 0-65535 " + std::to_string(port)
        );
    }
}

void ModbusSourceConfig::validateSlaveId(const int slaveId) const
{
    if(slaveId < 0 || slaveId > 248){
        throw std::runtime_error(
            "ModbusSourceConfig: slave id must be in rande 0-248 " 
            + std::to_string(slaveId)
        );
    }
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

void ModbusSourceConfig::validateModbusTypeSource(const std::string &typeSource) const
{
    if(validSourceTypes.count(typeSource) == 0){
        throw std::runtime_error(
            "ModbusSourceConfig: unsupported source type -> " + typeSource
        );
    }
}

void ModbusSourceConfig::validate(
    const std::string &id, 
    const std::string &ip, 
    const int port, 
    const int slaveId, 
    const int startAddress, 
    const std::string &typeSource) const
{
    validateId(id);
    validateIpv4(ip);
    validatePort(port);
    validateSlaveId(slaveId);
    validateStartAddress(startAddress);
    validateModbusTypeSource(typeSource);
}
