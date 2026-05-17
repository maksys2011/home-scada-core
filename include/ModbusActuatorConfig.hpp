#pragma once
#include <string>
#include <nlohmann/json.hpp>
#include <filesystem>
#include "BaseActuatorConfig.hpp"
#include "Enum.hpp"
using json = nlohmann::json;

class ModbusActuatorConfig : public BaseActuatorConfig
{
private:
    int startAddress_;
    double minValue_;
    double maxValue_;
    bool inverted_ = false;
    std::string transport_;

public:
    ModbusActuatorConfig() = default;
    ModbusActuatorConfig(
        const std::string& client_id,
        ActuatorType type, 
        bool defaultStatus,
        CommandType cmd,
        ActuatorConnectionType connection_type,
        int startAddress,
        const std::string& id,
        double minValue,
        double maxValue,
        bool inverted,
        int expectedIndex,
        const std::string& transport);
        
    ~ModbusActuatorConfig() = default;

    void fromJson(const json& j) override;
    void fromJson(const std::filesystem::path& path) override;
    bool validate() const override;
    void printInfo() const override;

    int getStartAddress() const { return startAddress_; };
    const std::string& getId() const { return id_; };
    double getMinValue() const { return minValue_; };
    double getMaxValue() const { return maxValue_; };
    bool getInverted() const { return inverted_; };
    int getExpectedIndex() const { return expectedIndex_; };
    const std::string& getTransport() const { return transport_; };
};

