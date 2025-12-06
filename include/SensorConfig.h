#pragma once
#include <string>
#include <Enum.h>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

class SensorConfig
{
        public:
        
        std::string id_;
        std::string name_;
        Type type_;
        double warnHigh_ = 0.0;
        double warnLow_ = 0.0;
        double alarmHigh_ = 0.0;
        double alarmLow_ = 0.0;

        public:

        SensorConfig() = default;

        SensorConfig(const std::string &id_,
                         const std::string &name_,
                         Type type_,
                         double warnHigh,
                         double warnLow,
                         double alarmHigh,
                         double alarmLow);

        void fromJson(const json &j);

        void fromJson(const std::string& path);

        const std::string &getId() const { return id_; };

        const std::string &getName() const { return name_; };

        Type getType() const { return type_; };

        double getWarnHigh() const { return warnHigh_; };

        double getWarnLow() const { return warnLow_; };

        double getAlarmHigh() const { return alarmHigh_; };

        double getAlarmLow() const { return alarmLow_; };

        bool validate() const;

        void print() const;
        
};
