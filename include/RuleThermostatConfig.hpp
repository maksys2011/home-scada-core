#pragma once

#include <nlohmann/json.hpp>
#include <string>
#include "RuleConfig.hpp"

using json = nlohmann::json;

class RuleThermostatConfig : public RuleConfig
{
private:
    double minTemp_;
    double maxTemp_;

public:
    void fromJson(const json& j) override;
    void fromJson(const std::string& path) override;
    bool validate()const override;
    void print()const override;

    double getMinTemp() const;
    double getMaxTemp() const;
};
