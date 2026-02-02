#pragma once
#include <string>
#include <filesystem>
#include <nlohmann.json/hpp>

#include "Enum.hpp"

using json = nlohmann::json;

class LightConfig
{
private:

    std::string id_;
    std::string name_;
    SensorType type_;
    std::string room_;
    bool enable_;
    std::string sensorId_;

public:

    LightConfig() = default;
    LightConfig(const std::string& id,
                const std::string& name,
                SensorType type,
                const std::string& room,
                bool enable,
                const std::string& sensorId);

    void fromJson(const std::string& path);
    void fromJson(const std::filesystem::path& path);
    void fromJson(json j);

    const std::string& getId() const {return id_;};
    const std::string& getName() const {return name_;};
    SensorType getType() const {return type_;};
    const std::string& getRoom() const {return room_;};
    const std::string& getSensorId() const {return sensorId_;};
};