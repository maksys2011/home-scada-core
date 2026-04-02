#pragma once
#include <string>
#include <filesystem>
#include <nlohmann/json.hpp>
#include <sstream>
#include <set>
#include "SourceConfig.hpp"
#include "Enum.hpp"
using json = nlohmann::json;

class ModbusSourceConfig : public SourceConfig
{
public:
    ModbusSourceConfig() = default;
    ModbusSourceConfig(
        const std::string& clientId,
        const std::string& sourceId,
        const std::string& ip,
        int port,
        int slave_Id,
        int startAddress,
        const std::string& typeNameSource
    );

    void fromJson(const std::filesystem::path& pathFile) override;
    void fromJson(const json& j) override;

    const std::string& getClientId() const { return client_id_; };
    const std::string& getSourceId() const  { return source_id_; };
    const std::string& getIp() const { return ip_; };
    int getPort() const { return port_; };
    int getSlaveId() const { return slave_Id_; };
    int getStartAddress() const { return startAddress_;};
    int getCount() const { return count_; };
    ModbusObjectType getTypeSource() const { return typeSource_; };
    
    void print() override;

    void validateStartAddress(const int startAddress) const;
    void validateModbusTypeSource(const std::string& typeSource) const;
    void validate(
        const std::string& client_id,
        const std::string& source_id,
        const std::string& ip,
        const int port,
        const int slaveId,
        const int startAddress,
        const std::string& typeSource) const;

private:
    std::string client_id_;
    std::string source_id_;
    std::string ip_;
    int port_ = 1502;
    int slave_Id_ = 1;
    int startAddress_ = 0;
    int count_ = 1;
    ModbusObjectType typeSource_ = ModbusObjectType::Unknowen;
    static inline const std::set<std::string> validSourceTypes{
        "Unknowen", 
        "Coil",
        "DiscreteInput",
        "InputRegister",
        "HoldingRegister"
    };
};