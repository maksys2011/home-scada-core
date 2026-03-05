#pragma once
#include <nlohmann/json.hpp>
#include <string>
#include <filesystem>
#include "RuleConfig.hpp"
#include "Enum.hpp"
using json = nlohmann::json;

class RuleThermostatConfig : public RuleConfig
{
private:
    std::string id_;
    std::string id_sensor;
    std::string id_actuator;
    double minTemp_;
    double maxTemp_;
    RuleType type_;

public:
    void fromJson(const json& j) override;
    void fromJson(const std::filesystem::path& path) override;
    
    bool validate()const override;
    void print()const override;

    double getMinTemp() const { return minTemp_; } ;
    double getMaxTemp() const { return maxTemp_; } ;
    std::string getId() const { return id_; } ;
    std::string getIdSensor() const { return id_sensor; } ;
    std::string getIdActuator() const { return id_actuator; } ;
};
