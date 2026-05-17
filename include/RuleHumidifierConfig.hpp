#pragma once
#include <nlohmann/json.hpp>
#include <string>
#include <filesystem>
#include "RuleConfig.hpp"
#include "Enum.hpp"
using json = nlohmann::json;

class RuleHumidifierConfig : public RuleConfig
{
public:
    void fromJson(const json& j) override;
    void fromJson(const std::filesystem::path& path) override;

    bool validate() const override;
    void print() const override;

    RuleType getRuleType() const override { return type_; };
    const std::string& getId() const { return id_; };
    const std::string& getSensorId() const override { return id_sensor_; };
    const std::string& getActuatorId() const override { return id_actuator_; };
    double getMinHumidity () const { return minHumidity_; };
    double getMaxHumidity () const { return maxHumidity_; };

private:
    std::string id_;
    std::string id_sensor_;
    std::string id_actuator_;
    double minHumidity_;
    double maxHumidity_;
    RuleType type_;
};