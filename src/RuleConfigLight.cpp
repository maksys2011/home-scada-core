#include "RuleConfigLight.hpp"
#include <iostream>
#include <fstream>
#include "utils.hpp"
using json = nlohmann::json;

RuleConfigLight::RuleConfigLight(
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
    double targetIlluminance,

    bool enabled,
    const std::string& type)
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

    enabled_(enabled),
    type_(ParseRuleType(type))
{}

void RuleConfigLight::fromJson(const std::filesystem::path &path)
{
    std::ifstream file = scada::utils::create_json_ifstream(path);
    json j;
    file >> j;
    fromJson(j);
}

void RuleConfigLight::fromJson(const json& j)
{
    id_ = scada::utils::check_the_key<std::string>(j, "id_");
    name_ = scada::utils::check_the_key<std::string>(j, "name_");
    room_ = scada::utils::check_the_key<std::string>(j, "room_");
    id_sensor = scada::utils::check_the_key<std::string>(j, "id_sensor");
    id_actuator = scada::utils::check_the_key<std::string>(j, "id_actuator");
    maxLux_ = scada::utils::check_the_key<double>(j, "maxLux_");
    minLux_ = scada::utils::check_the_key<double>(j, "minLux_");
    if(j.contains("night_")){
        const auto& nightJson = j.at("night_");
        night_.fromHour = nightJson.value("fromHour", 21);
        night_.toHour = nightJson.value("toHour", 7);
        night_.fixedPosition = nightJson.value("fixedPosition", 80);
    }
    if(j.contains("day_")){
        const auto& dayJson = j.at("day_");
        day_.fromHour = dayJson.value("fromHout", 7);
        day_.toHour = dayJson.value("toHour", 21);
        day_.fixedPosition = dayJson.value("fixedPosition", -1);
    }
    targetIlluminance_ = scada::utils::check_the_key<double>(j, "targetIlluminance_");
    enabled_ = scada::utils::check_the_key<bool>(j, "enable_");
    type_ = ParseRuleType(scada::utils::check_the_key<std::string>(j, "type"));
}

bool RuleConfigLight::validate() const
{
    return false;
}

void RuleConfigLight::print() const
{
    std::cout << "RuleLightConfig {" << std::endl;
    std::cout << "type: " << RuleTypeToString(type_) << std::endl;
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