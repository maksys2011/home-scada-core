#pragma once
#include <string>
#include <filesystem>
#include <nlohmann/json.hpp>
#include "SourceConfig.hpp"
#include "utils.hpp"

using json = nlohmann::json;

class MqttSourceConfig : public SourceConfig
{
public:
    MqttSourceConfig() = default;
    MqttSourceConfig(
        std::string& name,
        std::string& sourceId,
        std::string& broker,
        std::string& clientId,
        std::string& topic,
        int qos
    );
    void fromJson(const json& j) override;
    void fromJson(const std::filesystem::path& path) override;

    const std::string& getName() const { return name_; };
    const std::string& getSourceId() const { return sourceId_; };
    const std::string& getBroker() const { return broker_; };
    const std::string& getClient() const { return clientId_; };
    const std::string& getTopic() const { return topic_; };
    int getQos() const { return qos_; };

    void print() override;

    void validate();

private:
    std::string name_;
    std::string sourceId_;
    std::string broker_;
    std::string clientId_;
    std::string topic_;
    int qos_ = 0;
};