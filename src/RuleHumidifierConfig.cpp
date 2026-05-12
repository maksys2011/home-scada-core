#include "RuleHumidifierConfig.hpp"
#include <fstream>
#include "utils.hpp"

void RuleHumidifierConfig::fromJson(const json &j)
{
    id_ = scada::utils::check_the_key<std::string>(j,"id");
    id_sensor_ = scada::utils::check_the_key<std::string>(j, "id_sensor");
    id_actuator_ = scada::utils::check_the_key<std::string>(j, "id_actutor");
    minHumidity_ = scada::utils::check_the_key<double>(j, "minHumidity");
    maxHumidity_ = scada::utils::check_the_key<double>(j, "maxHumidity");

    if(!validate()){
        throw std::runtime_error(
            "Invalid humidifier config: maxHumidity must be greater than minHumidity and delta must be positive");
    }

}
void RuleHumidifierConfig::fromJson(const std::filesystem::path &path)
{
    std::ifstream file = scada::utils::create_json_ifstream(path);

    json j;
    file >> j;

    fromJson(j);
}

bool RuleHumidifierConfig::validate() const
{
    return minHumidity_ <= maxHumidity_;
}

void RuleHumidifierConfig::print() const
{

}

