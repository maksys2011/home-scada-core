#pragma once
#include <string>
#include <filesystem>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

class ModbusClientConfig
{
public:
    ModbusClientConfig() = default;
    ModbusClientConfig(const std::string& nameClient, const std::string& ip, int port, int slaveId);

    void fromJson(const std::filesystem::path& path);
    void fromJson(const json& j);
    
    const std::string& getNameClient()const { return nameClient_; };
    const std::string& getIp() const { return ip_; };
    int getPort() const { return port_; };
    int getSlaveId() const { return slaveId_; };

    void validate(
        const std::string& name, 
        const std::string& ip, 
        const int port, 
        const int slaveId) const;

    void testPrint() const;
    
private:
    std::string nameClient_;
    std::string ip_;
    int port_;
    int slaveId_;
};