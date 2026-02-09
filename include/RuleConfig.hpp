#pragma once

#include <string>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

class RuleConfig
{
public:
    virtual~ RuleConfig() = default;
    virtual void fromJson(const json& j) = 0;
    virtual void fromJson(const std::string& path) = 0;
    virtual bool validate()const = 0;
    virtual void print()const = 0;
};