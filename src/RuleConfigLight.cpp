#include "RuleConfigLight.hpp"
#include <iostream>
#include <fstream>
using json = nlohmann::json;

RuleConfigLight::RuleConfigLight(
                        const std::string& id, 
                        const std::string& name, 
                        const std::string& room,
                        const std::string& idSensor,
                        const std::string& idActuator,
                        bool enable, 
                        double maxLux,
                        double minLux)
    :
    id_(std::move(id)),
    name_(std::move(name)),
    room_(std::move(room)),
    enable_(enable),
    id_sensor(std::move(idSensor)),
    id_actuator(std::move(idActuator)),
    maxLux_(maxLux),
    minLux_(minLux){}

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