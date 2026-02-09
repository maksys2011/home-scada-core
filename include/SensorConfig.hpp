#pragma once
#include <string>
#include <Enum.hpp>
#include <nlohmann/json.hpp>
#include <filesystem>
#include <optional>
#include <chrono>

using json = nlohmann::json;

class SensorConfig{

private: 
        std::string id_;
        std::string name_;
        SensorType type_;
        double physicalMin_;
        double physicalMax_;
        double noiseEpsilon_;
        std::chrono::seconds staleTimeout_;
        double warnHigh_ = 0.0;
        double warnLow_  = 0.0;
        double alarmHigh_= 0.0;
        double alarmLow_ = 0.0;        
        double deadband_;
        double hysteresis_;
        bool enabled_;

public:
        SensorConfig() = default;
        SensorConfig(        
                const std::string& id,
                const std::string& name,
                SensorType type,
                double physicalMin,
                double physicalMax,
                double noiseEpsilon,
                std::chrono::seconds staleTimeout,
                double warnHigh,
                double warnLow,
                double alarmHigh,
                double alarmLow,        
                double deadband,
                double hysteresis,
                bool enabled);

        void fromJson(const json &j);
        void fromJson(const std::filesystem::path& path);
        void fromJson(const std::string& path);
        const std::string& getId() const { return id_; };
        const std::string& getName() const { return name_; };
        SensorType getType() const { return type_; };
        double getWarnHigh() const { return warnHigh_; };
        double getWarnLow() const { return warnLow_; };
        double getAlarmHigh() const { return alarmHigh_; };
        double getAlarmLow() const { return alarmLow_; };
        double deadband() const {return deadband_;}
        double hysteresis() const {return hysteresis_;}
        bool validate() const;
        bool validateValue(double v) const;
        void print() const;
};
