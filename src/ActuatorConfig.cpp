#include <SensorConfig.hpp>
#include <iostream>
#include <fstream>
#include "ActuatorConfig.hpp"
using json = nlohmann::json;

ActuatorConfig::ActuatorConfig(const std::string &id, 
                                const std::string &name, 
                                ActuatorType type, 
                                double minValue, 
                                double maxValue)
        :   id_(id),
            name_(name),
            type_(type),
            minValue_(minValue),
            maxValue_(maxValue)
{}

void ActuatorConfig::fromJson(const json &j)
{
    id_ = j.at("id").get<std::string>();
    name_ = j.at("name").get<std::string>();
    type_ = ParseActuatorType(j.at("type").get<std::string>());
    minValue_ = j.at("minValue").get<double>();
    maxValue_ = j.at("maxValue").get<double>();
}

void ActuatorConfig::fromJson(const std::filesystem::path &path)
{   
    std::ifstream file(path);
    if(!file){
        throw std::runtime_error("cannot open config file" + path.string());
    }
    json j;
    file >> j;
    fromJson(j);
}

void ActuatorConfig::fromJson(const std::string &path)
{
    std::ifstream file(path);
    if(!file){
        throw std::runtime_error("cannot open config file" + path);
    }
    json j;
    file >> j;
    fromJson(j);
}

bool ActuatorConfig::validate() const
{
    if(minValue_ <= maxValue_){
        return true;
    }
    return false;
}

void ActuatorConfig::print() const
{
    std::cout << "ActuatorConfig: " << std::endl;
    std::cout << "  id: " << id_ << std::endl;
    std::cout << "  name: " << name_ << std::endl;
    std::cout << "  type: ";
    std::cout << ActuatorTypeToString(type_) << std::endl;
    std::cout << "  Default state: " << (defaultState_ ==  false ? "ON" : "OFF") << std::endl; 
    std::cout << "  minValue: " << minValue_ << std::endl;
    std::cout << "  maxValue: " << maxValue_ << std::endl;
}
