#pragma once
#include <string>
#include <filesystem>
#include <nlohmann/json.hpp>
#include "Enum.hpp"
using json = nlohmann::json;

class RuleConfigLight
{
private:

    std::string id_;
    std::string name_;
    std::string room_;
    bool enable_;
    std::string sensorId_;

public:

    RuleConfigLight() = default;
    RuleConfigLight(const std::string& id,
                const std::string& name,
                const std::string& room,
                bool enable,
                const std::string& sensorId);

    void fromJson(const std::string& path);
    void fromJson(const std::filesystem::path& path);
    void fromJson(const json& j);

    const std::string& getId() const {return id_;};
    const std::string& getName() const {return name_;};
    const std::string& getRoom() const {return room_;};
    const std::string& getSensorId() const {return sensorId_;};

    void print() const;
};