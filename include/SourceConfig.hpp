#pragma once
#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;

class SourceConfig
{
public:
    virtual ~SourceConfig() = default;
    virtual void fromJson(const json& j) = 0;
    virtual void fromJson(const std::filesystem::path& path) = 0;
    virtual const std::string getTypeSource() = 0;
    virtual void print() = 0;
};