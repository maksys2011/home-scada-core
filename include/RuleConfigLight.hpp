#pragma once
#include <string>
#include <filesystem>
#include <nlohmann/json.hpp>

#include "Enum.hpp"
#include "RuleConfig.hpp"

using json = nlohmann::json;

class RuleConfigLight : public RuleConfig
{
private:
    std::string id_;
    std::string name_;
    std::string room_;
    std::string id_sensor;
    std::string id_actuator;
    size_t timer = 0;
    const size_t DAY_DURATION = 100;
    bool enable_;
    double maxLux_;
    double minLux_;
    int hysteresis_;
    ControlMode selectes_ = ControlMode::Auto;
    int currentPosition_ = 0;
    int targetPosition_ = 0;
    size_t luxTimerCounte_ = 0;
    size_t morningTime_ = 0;
    size_t dayTime_ = 6;
    size_t eveningTime_ = 51;

public:
    RuleConfigLight() = default;
    RuleConfigLight(
    const std::string& id,
    const std::string& name,
    const std::string& room,
    const std::string& id_sensor,
    const std::string& id_actuator,
    bool enable,
    double maxLux,
    double minLux,
    int hysteresis,
    int currentPosition,
    int targetPosition,
    size_t luxTimerCounte,
    size_t morningTime,
    size_t dayTime,
    size_t eveningTime 
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