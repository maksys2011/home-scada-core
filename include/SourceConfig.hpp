#pragma once

#include <nlohmann/json.hpp>

using json = nlohmann::json;

class SourceConfig
{
public:
    virtual void fromJson(const json& j) = 0;
    virtual void fromJson(const std::filesystem::path& path) = 0;
    virtual void print() = 0;
};