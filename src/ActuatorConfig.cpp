#include <SensorConfig.hpp>
#include <iostream>
#include <fstream>
#include "ActuatorConfig.hpp"
#include "utils.hpp"
using json = nlohmann::json;

ActuatorConfig::ActuatorConfig(
    const std::string& client_id,
    int startAddress,
    const std::string& id, 
    const std::string& name, 
    ActuatorType type, 
    double minValue, 
    double maxValue):
    client_id_(client_id),
    startAddress_(startAddress),
    id_(id),
    name_(name),
    type_(type),
    minValue_(minValue),
    maxValue_(maxValue)
{}

void ActuatorConfig::fromJson(const json& j)
{
    client_id_ = scada::utils::check_the_key<std::string>(j, "client_id");
    startAddress_ = scada::utils::check_the_key<int>(j, "startAddress");
    id_ = scada::utils::check_the_key<std::string>(j, "id");
    name_ = scada::utils::check_the_key<std::string>(j, "name");
    type_ = ParseActuatorType(scada::utils::check_the_key<std::string>(j, "type"));
    minValue_ = scada::utils::check_the_key<double>(j, "minValue");
    maxValue_ = scada::utils::check_the_key<double>(j, "maxValue");
}

void ActuatorConfig::fromJson(const std::filesystem::path& path)
{   
    std::ifstream file = scada::utils::create_json_ifstream(path);
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
