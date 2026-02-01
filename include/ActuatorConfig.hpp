#pragma once
#include <string>
#include <Enum.hpp>
#include <nlohmann/json.hpp>
#include <filesystem>
using json = nlohmann::json;

class ActuatorConfig
{
private:
        std::string id_;
        std::string name_;
        ActuatorType type_;
        
        double minValue_ = 0.0;
        double maxValue_ = 1.0;
        bool defaultState_ = false;

        bool inverted_ = false;

public:
        ActuatorConfig() = default;
        ActuatorConfig(const std::string &id_,
                        const std::string &name_,
                        ActuatorType type_,
                        double minValue,
                        double maxValue);

        void fromJson(const json &j);
        void fromJson(const std::filesystem::path& path);
        void fromJson(const std::string& path);
        const std::string &getId() const { return id_; };
        const std::string &getName() const { return name_; };
        ActuatorType getType() const { return type_; };
        double getMinValue() const { return minValue_; };
        double getMaxValue() const { return maxValue_; };
        bool validate() const;
        void print() const;
};
