#include <SensorConfig.hpp>
#include <iostream>
#include <fstream>
#include "ActuatorConfig.hpp"
#include "utils.hpp"
using json = nlohmann::json;

ActuatorConfig::ActuatorConfig(
    const std::string &client_id, 
    int startAddress, 
    const std::string &id, 
    const std::string &actuator_type, 
    ActuatorType type, 
    double minValue, 
    double maxValue, 
    int expectedIndex, 
    const std::string &cmd, 
    const std::string transport) :
    client_id_(client_id),
    startAddress_(startAddress),
    id_(id),
    actuator_type_(actuator_type),
    type_(type),
    minValue_(minValue),
    maxValue_(maxValue),
    expectedIndex_(expectedIndex),
    cmd_(ParceCommandType(cmd)),
    transport_(transport)
{}

void ActuatorConfig::fromJson(const json &j)
{
    client_id_ = scada::utils::check_the_key<std::string>(j, "client_id");
    startAddress_ = scada::utils::check_the_key<int>(j, "startAddress");
    id_ = scada::utils::check_the_key<std::string>(j, "id");
    actuator_type_ = scada::utils::check_the_key<std::string>(j, "actuator_type");
    type_ = ParseActuatorType(scada::utils::check_the_key<std::string>(j, "type"));
    minValue_ = scada::utils::check_the_key<double>(j, "minValue");
    maxValue_ = scada::utils::check_the_key<double>(j, "maxValue");
    std::string indexCmd = scada::utils::check_the_key<std::string>(j, "expectedIndex");
    expectedIndex_ = scada::utils::getTeamIndex(indexCmd);
    cmd_ = ParceCommandType(scada::utils::check_the_key<std::string>(j, "commandType"));
    transport_ = scada::utils::check_the_key<std::string>(j, "transport");
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
    std::cout << "  type: " << actuator_type_ << std::endl;
    std::cout << "  client id: " << client_id_ << std::endl;
    // std::cout << ActuatorTypeToString(type_) << std::endl;
    std::cout << "  Default state: " << (defaultState_ ==  false ? "ON" : "OFF") << std::endl; 
    std::cout << "  minValue: " << minValue_ << std::endl;
    std::cout << "  maxValue: " << maxValue_ << std::endl;
    std::cout << "  command: " << (ParceCommandTypeToString(cmd_)) << std::endl; 
    std::cout << "  indexCmd: " << expectedIndex_ << std::endl;
    std::cout << "  transport: " << transport_ << std::endl;
}
