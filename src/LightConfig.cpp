#include "LightConfig.hpp"
#include <iostream>
#include <fstream>
using json = nlohmann::json;

LightConfig::LightConfig(
                        const std::string &id, 
                        const std::string &name, 
                        SensorType type, 
                        const std::string &room, 
                        bool enable, 
                        const std::string &sensorId)
    :
    id_(std::move(id)),
    name_(std::move(name)),
    type_(type),
    room_(std::move(room)),
    enable_(enable),
    sensorId_(std::move(sensorId))
{}

void LightConfig::fromJson(const std::string &path)
{
    std::ifstream file(path);
    if(!file.is_open()){
        throw std::runtime_error("cannot open lightconfig file" + path);
    }
    json j;
    file >> j;
    fromJson(j);
}

void LightConfig::fromJson(const std::filesystem::path &path)
{
    std::ifstream file(path);
    if(!file.is_open()){
        throw std::runtime_error("cannot open lightconfig file" + path.string());
    }
    json j;
    file >> j;
    fromJson(j);
}

void LightConfig::fromJson(const json& j)
{
    id_ = j.at("id_").get<std::string>();
    name_ = j.at("name_").get<std::string>();
    type_ = ParseSensorType(j.at("type_").get<std::string>());
    room_ = j.at("room_").get<std::string>();
    enable_ = j.at("enable_").get<bool>();
    sensorId_ = j.at("sensorId_").get<std::string>();
}

void LightConfig::print() const
{
    std::cout << "LightConfig {" << std::endl;
    std::cout << "  id: " << id_ << std::endl;
    std::cout << "  name: " << name_ << std::endl;
    std::cout << "  type: ";
    std::cout << SensorTypeToString(type_) << std::endl;
    std::cout << "  room: " << room_ << std::endl;
    std::cout << "  enable: " << (enable_? "ON" : "OFF") << std::endl;
    std::cout << "}" << std::endl;
}
