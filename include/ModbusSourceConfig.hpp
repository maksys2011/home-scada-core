#include <string>
#include <filesystem>
#include <nlohmann/json.hpp>
#include "Enum.hpp"
using json = nlohmann::json;

/// @brief Конфигурация Modbus-источника данных (TCP)  

class ModbusSourceConfig
{
public:
    ModbusSourceConfig(
        const std::string& ip,
        int port,
        int slave_Id,
        int startAddress,
        const std::string& typeNameSource
    );

    void fromJson(const std::filesystem::path& pathFile);
    void fromJson(const json& j);

    const std::string& getIp() {return ip_;};
    int getPort() const {return port_;};
    int getSlaveId() const {return slave_Id_;};
    int getStartAddress() const {return startAddress_;};
    int getCount() const {return count_;};
    ModbusObjectType getTypeSource() const {return typeSource_;};
    void testPrintInfo() const;

private:
    std::string ip_;
    int port_ = 1502;
    int slave_Id_ = 1;
    int startAddress_ = 0;
    int count_ = 1;
    ModbusObjectType typeSource_ = ModbusObjectType::Unknowen;

};