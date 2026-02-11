#pragma once
#include <string>
#include <filesystem>
#include <nlohmann/json.hpp>

#include "Enum.hpp"
#include "RuleConfig.hpp"

using json = nlohmann::json;

struct TimeWindow{
    int fromHour;
    int toHour;
    int fixedPosition;
};

class RuleConfigLight : public RuleConfig
{
private:
    std::string id_;
    std::string name_;
    std::string room_;

    std::string id_sensor;
    std::string id_actuator;

    double maxLux_;
    double minLux_;
    size_t confirmTicks_; // гистерезис - принимаем 3

    TimeWindow night_ {21, 7, 80};  // период с 9 до 7
    TimeWindow day_ {7, 21, -1};    // период с 7 до 9

    bool enabled_;

public:
    RuleConfigLight() = default;
    RuleConfigLight(
    const std::string& id,
    const std::string& name,
    const std::string& room,

    const std::string& id_sensor,
    const std::string& id_actuator,

    double maxLux,
    double minLux,
    size_t confirmTicks,

    TimeWindow night,
    TimeWindow day,
    
    bool enabled
    );

    void fromJson(const std::string& path) override;
    void fromJson(const std::filesystem::path& path);
    void fromJson(const json& j) override;
    const std::string& getId() const {return id_;};
    const std::string& getName() const {return name_;};
    const std::string& getRoom() const {return room_;};
    const std::string getIdSensor() const {return id_sensor;};
    const std::string getIdActuator() const {return id_actuator;};
    double getMaxLux() {return maxLux_;};
    double getMinLux() {return minLux_;};
    bool validate() const override;
    void print() const override;
};