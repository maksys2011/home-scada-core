#pragma once
#include <string>
#include <Enum.hpp>
#include <nlohmann/json.hpp>
#include <filesystem>
using json = nlohmann::json;

class ActuatorConfig
{
private:
        std::string client_id_;
        int startAddress_;
        std::string id_;
        std::string name_;
        ActuatorType type_;
        
        double minValue_ = 0.0;
        double maxValue_ = 1.0;
        bool defaultState_ = false;

        bool inverted_ = false;

public:
        ActuatorConfig() = default;
        ActuatorConfig(
                const std::string& client_id,
                int startAddress,
                const std::string& id,
                const std::string& name,
                ActuatorType type,
                double minValue,
                double maxValue);

        void fromJson(const json& j);
        void fromJson(const std::filesystem::path& path);

        const std::string& getIdClient() const { return client_id_; };
        int getStartAddress () const { return startAddress_; };
        const std::string& getId() const { return id_; };
        const std::string& getName() const { return name_; };
        ActuatorType getType() const { return type_; };
        double getMinValue() const { return minValue_; };
        double getMaxValue() const { return maxValue_; };
        bool validate() const;
        void print() const;
};
