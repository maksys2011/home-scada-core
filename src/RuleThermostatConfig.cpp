#include <iostream>
#include <fstream>
#include "RuleThermostatConfig.hpp"
#include "utils.hpp"

void RuleThermostatConfig::fromJson(const json &j)
{
    id_ = scada::utils::check_the_key<std::string>(j, "rule_id");
    id_sensor = scada::utils::check_the_key<std::string>(j, "sensor_id");
    id_actuator = scada::utils::check_the_key<std::string>(j, "actuator_id");
    minTemp_ = scada::utils::check_the_key<double>(j, "minTemp");
    maxTemp_ = scada::utils::check_the_key<double>(j, "maxTemp");
    type_ = ParseRuleType(scada::utils::check_the_key<std::string>(j, "type"));

    if(!validate()){
        throw std::runtime_error(
            "Invalid thermostat config: maxTemp must be greater than minTemp and delta must be sufficient");
    }
}

void RuleThermostatConfig::fromJson(const std::filesystem::path &path)
{
    std::ifstream file = scada::utils::create_json_ifstream(path);
    json j;
    file >> j;
    fromJson(j);
}

bool RuleThermostatConfig::validate() const
{
    return maxTemp_ > minTemp_;
}

void RuleThermostatConfig::print() const
{
    std::cout << "Type : Thermostat" << std::endl;
    std::cout << "Rule id: "  << getId() << std::endl;
    std::cout << "MinValue: " << getMinTemp() << std::endl;
    std::cout << "MaxValue: " << getMaxTemp() << std::endl;
    std::cout << "type: " << RuleTypeToString(type_) << std::endl;
}
