#pragma once
#include <string>
#include <nlohmann/json.hpp>
#include <filesystem>
#include "BaseActuatorConfig.hpp"
#include "Enum.hpp"
using json = nlohmann::json;

class MqttActuatorConfig : public BaseActuatorConfig
{
private:
    std::string broker_;
    std::string topic_;
    std::string transport_;

public:
    MqttActuatorConfig() = default;
    MqttActuatorConfig(
        const std::string& client_id,
        ActuatorType type, 
        bool defaultStatus,
        CommandType cmd,
        ActuatorConnectionType connection_type,
        const std::string& id,
        const std::string& broker,
        const std::string& topic,
        int expectedIndex,
        const std::string& transport);
    ~MqttActuatorConfig() = default;
    
    void fromJson(const json& j) override;
    void fromJson(const std::filesystem::path& path) override;
    bool validate() const override;
    void printInfo() const override;

    const std::string& getTopic() const { return topic_; };
};

