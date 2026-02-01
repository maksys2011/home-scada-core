#pragma once

#include <nlohmann/json.hpp>
#include <string>
#include <filesystem>

#include "RuleConfig.hpp"

using json = nlohmann::json;

class RuleThermostatConfig : public RuleConfig
{
private:
    std::string id_;
    std::string id_sensor;
    std::string id_actuator;
    double minTemp_;
    double maxTemp_;

public:
    void fromJson(const json& j) override;
    void fromJson(const std::string& path) override;
    void fromJson(const std::filesystem::path& path);
    bool validate()const override;
    void print()const override;
    double getMinTemp() const;
    double getMaxTemp() const;
    std::string getId() const;
    std::string getIdSensor() const;
    std::string getIdActuator() const;
};
