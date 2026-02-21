#include <string>
#include <filesystem>
#include <nlohmann/json.hpp>
#include <sstream>
#include <set>
#include "Enum.hpp"
using json = nlohmann::json;

/// @brief Конфигурация Modbus-источника данных (TCP)  

class ModbusSourceConfig
{
public:
    ModbusSourceConfig() = default;
    ModbusSourceConfig(
        const std::string& id,
        const std::string& ip,
        int port,
        int slave_Id,
        int startAddress,
        const std::string& typeNameSource
    );

    void fromJson(const std::filesystem::path& pathFile);
    void fromJson(const json& j);


    const std::string& getId() {return id_;};
    const std::string& getIp() {return ip_;};
    int getPort() const {return port_;};
    int getSlaveId() const {return slave_Id_;};
    int getStartAddress() const {return startAddress_;};
    int getCount() const {return count_;};
    ModbusObjectType getTypeSource() const {return typeSource_;};
    
    void testPrintInfo() const;

    /// @brief валидация полей 
    /// @param ip 
    /// @return 
    void validateId(const std::string& id)const;
    void validateIpv4(const std::string& ip)const;
    void validatePort(const int port)const;
    void validateSlaveId(const int slaveId) const;
    void validateStartAddress(const int startAddress) const;
    void validateModbusTypeSource(const std::string& typeSource) const;
    void validate(const std::string& id,
                    const std::string& ip,
                    const int port,
                    const int slaveId,
                    const int startAddress,
                    const std::string& typeSource) const;

private:
    std::string id_;
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