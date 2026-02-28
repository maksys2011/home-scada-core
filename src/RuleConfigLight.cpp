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

    double maxLux, 
    double minLux, 
    size_t confirmTicks, 

    TimeWindow night, 
    TimeWindow day,
    double targetIlluminance,

    bool enabled)
    :
    id_(id),
    name_(name),
    room_(room),

    id_sensor(id_sensor),
    id_actuator(id_actuator),

    maxLux_(maxLux),
    minLux_(minLux),
    confirmTicks_(confirmTicks),

    night_(night),
    day_(day),
    targetIlluminance_(targetIlluminance),

    enabled_(enabled)
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
    if(j.contains("id_")){
        id_ = j.at("id_").get<std::string>();
    }else{
        throw std::runtime_error(
            "there is no required key= id"
        );
    }
    
    if(j.contains("name_")){
       name_ = j.at("name_").get<std::string>(); 
    }else{
        throw std::runtime_error(
            "there is no required key= name_"
        );
    }

    if(j.contains("room_")){
       room_ = j.at("room_").get<std::string>();
    }else{
        throw std::runtime_error(
            "there is no required key= room_"
        );
    }

    if(j.contains("id_sensor")){
        id_sensor = j.at("id_sensor").get<std::string>();
    }else{
        throw std::runtime_error(
            "there is no required key= id_sensor"
        );
    }
    
    if(j.contains("id_actuator")){
        id_actuator = j.at("id_actuator").get<std::string>();
    }else{
        throw std::runtime_error(
            "there is no required key= id_actuator"
        );
    }
    
    if(j.contains("maxLux_")){
        maxLux_ = j.at("maxLux_").get<double>();
    }else{
        throw std::runtime_error(
            "there is no required key= maxLux"
        );
    }

    if(j.contains("minLux_")){
        minLux_ = j.at("minLux_").get<double>();
    }else{
        throw std::runtime_error(
            "there is no required key= minLux"
        );
    }

    if(j.contains("night_")){
        
        const auto& ninghtJson = j.at("night_");

        night_.fromHour = ninghtJson.value("fromHour", 21);
        night_.toHour = ninghtJson.value("toHour", 7);
        night_.fixedPosition = ninghtJson.value("fixedPosition", 80);

    }else{
        night_ = {21, 7, 80};
    }

    if(j.contains("day_")){

        const auto& dayJson = j.at("day_");
        
        day_.fromHour = dayJson.value("fromHout", 7);
        day_.toHour = dayJson.value("toHour", 21);
        day_.fixedPosition = dayJson.value("fixedPosition", -1);

    }else{
        day_ = {7, 21, -1};
    }

    if(j.contains("targetIlluminance_")){
        targetIlluminance_ = j.at("targetIlluminance_").get<double>();
    }else{
        throw std::runtime_error(
            "there is no required key= targetIlluminance"
        );
    }

    if(j.contains("enabled_")){
        enabled_ = j.at("enabled_").get<bool>();
    }else{
        enabled_ = true;
    }
}

bool RuleConfigLight::validate() const
{
    return false;
}

void RuleConfigLight::print() const
{
    std::cout << "RuleLightConfig {" << std::endl;
    std::cout << "  id: " << id_ << std::endl;
    std::cout << "  name: " << name_ << std::endl;
    std::cout << "  room: " << room_ << std::endl;
    std::cout << "  enable: " << (enabled_? "ON" : "OFF") << std::endl;
    std::cout << "}" << std::endl;

    std::cout << "Time of night mode {" << std::endl;
    std::cout << "  night: " << std::endl;
    std::cout << "  fronHour: " << night_.fromHour << std::endl;
    std::cout << "  toHour  : " << night_.toHour << std::endl;
    std::cout << "  operiton mode: " << (night_.fixedPosition == 80 ? "AUTO" : "MANUAL") << std::endl;

    std::cout << "Time of day mode {" << std::endl;
    std::cout << "  day: " << std::endl;
    std::cout << "  fronHour: " << day_.fromHour << std::endl;
    std::cout << "  toHour  : " << day_.toHour << std::endl;
    std::cout << "  operiton mode: " << (day_.fixedPosition == 80 ? "AUTO" : "MANUAL") << std::endl;

    std::cout << std::endl;

    std::cout << "  light_setpoint: " << targetIlluminance_ << std::endl;
}