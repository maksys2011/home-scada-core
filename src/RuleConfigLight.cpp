#include "RuleConfigLight.hpp"
#include <iostream>
#include <fstream>
using json = nlohmann::json;

RuleConfigLight::RuleConfigLight(
    const std::string &id, 
    const std::string &name, 
    const std::string &room, 
    const std::string &id_sensor, 
    const std::string &id_actuator, 
    bool enable, 
    double maxLux, 
    double minLux, 
    int hysteresis, 
    int currentPosition, 
    int targetPosition, 
    size_t luxTimerCounte, 
    size_t morningTime, 
    size_t dayTime, 
    size_t eveningTime)
    :
    id_(std::move(id)),
    name_(std::move(name)),
    room_(std::move(room)),
    id_sensor(std::move(id_sensor)),
    id_actuator(std::move(id_actuator)),
    enable_(enable),
    maxLux_(maxLux),
    minLux_(minLux),
    hysteresis_(hysteresis),
    currentPosition_(currentPosition),
    targetPosition_(targetPosition),
    luxTimerCounte_(luxTimerCounte),
    morningTime_(morningTime),
    dayTime_(dayTime),
    eveningTime_(eveningTime)
{}

void RuleConfigLight::fromJson(const std::string &path)
{
    std::ifstream file(path);
    if(!file.is_open()){
        throw std::runtime_error("cannot open lightconfig file" + path);
    }
    json j;
    file >> j;
    fromJson(j);
}

void RuleConfigLight::fromJson(const std::filesystem::path &path)
{
    std::ifstream file(path);
    if(!file.is_open()){
        throw std::runtime_error("cannot open lightconfig file" + path.string());
    }
    json j;
    file >> j;
    fromJson(j);
}

void RuleConfigLight::fromJson(const json& j)
{
    id_ = j.at("rule_id").get<std::string>();
    name_ = j.at("name_").get<std::string>();
    room_ = j.at("room_").get<std::string>();
    id_sensor = j.at("id_sensor").get<std::string>();
    id_actuator = j.at("id_actuator").get<std::string>();
    enable_ = j.at("enable_").get<bool>();
    minLux_ = j.at("minLux").get<double>();
    maxLux_ = j.at("maxLux").get<double>();
}

bool RuleConfigLight::validate() const
{
    return false;
}

void RuleConfigLight::print() const
{
    std::cout << "LightConfig {" << std::endl;
    std::cout << "  id: " << id_ << std::endl;
    std::cout << "  name: " << name_ << std::endl;
    std::cout << "  room: " << room_ << std::endl;
    std::cout << "  enable: " << (enable_? "ON" : "OFF") << std::endl;
    std::cout << "}" << std::endl;
}