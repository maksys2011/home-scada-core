#include <iostream>
#include <fstream>
#include "RuleThermostatConfig.hpp"

void RuleThermostatConfig::fromJson(const json &j)
{
    minTemp_ = j.at("minTemp").get<double>();
    maxTemp_ = j.at("maxTemp").get<double>();
    if(!validate()){
        throw std::runtime_error(
            "Invalid thermostat config: maxTemp must be greater than minTemp and delta must be sufficient");
    }
}

void RuleThermostatConfig::fromJson(const std::string &path)
{
    std::ifstream file(path);
    if(!file){
        throw std::runtime_error("cannot open ruleConfig file" + path);
    }
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
    std::cout << "MinValue: " << getMinTemp() << std::endl;
    std::cout << "MaxValue: " << getMaxTemp() << std::endl;
}

double RuleThermostatConfig::getMinTemp() const
{
    return minTemp_;
}

double RuleThermostatConfig::getMaxTemp() const
{
    return maxTemp_;
}
