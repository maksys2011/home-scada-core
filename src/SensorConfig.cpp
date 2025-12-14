#include <SensorConfig.hpp>
#include <iostream>
#include <fstream>
#include <cmath>
using json = nlohmann::json;

SensorConfig::SensorConfig(const std::string &id,
                            const std::string &name,
                            SensorType type,
                            double warnHigh,
                            double warnLow,
                            double alarmHigh,
                            double alarmLow,
                            double deadband,
                            double hysteresis)
    : id_(id),
      name_(name),
      type_(type),
      warnHigh_(warnHigh),
      warnLow_(warnLow),
      alarmHigh_(alarmHigh),
      alarmLow_(alarmLow),
      deadband_(deadband),
      hysteresis_(hysteresis)
      {}

void SensorConfig::fromJson(const json &j)
{
    id_ = j.at("id_").get<std::string>();
    name_ = j.at("name_").get<std::string>();
    type_ = ParseSensorType(j.at("type_").get<std::string>());
    warnHigh_ = j.at("warnHigh_").get<double>();
    warnLow_ = j.at("warnLow_").get<double>();
    alarmHigh_ = j.at("alarmHigh_").get<double>();
    alarmLow_ = j.at("alarmLow_").get<double>();
    deadband_ = j.at("deadband_").get<double>();
    hysteresis_ = j.at("hysteresis_").get<double>();
}
void SensorConfig::fromJson(const std::string &path)
{
    std::ifstream file(path);
    if(!file){
        throw std::runtime_error("cannot open config file" + path);
    }
    json j;
    file >> j;
    fromJson(j);
}

bool SensorConfig::validate() const
{
    return alarmLow_ <= warnLow_ && warnLow_ <= warnHigh_ && warnHigh_ <= alarmHigh_;
}

bool SensorConfig::validateValue(double v) const
{
    if (!validate()) {
        std::cout << "validate - false" << std::endl;
        return false;
    }
    return  std::isfinite(v);
}

void SensorConfig::print() const
{
    std::cout << "SensorConfig {" << std::endl;
    std::cout << "  id: " << id_ << std::endl;
    std::cout << "  name: " << name_ << std::endl;
    std::cout << "  type: ";
    std::cout << SensorTypeToString(type_) << std::endl;
    std::cout << "  warnHigh: " << warnHigh_ << std::endl;
    std::cout << "  warnLow: " << warnLow_ << std::endl;
    std::cout << "  alarmHigh: " << alarmHigh_ << std::endl;
    std::cout << "  alarmLow: " << alarmLow_ << std::endl;
    std::cout << "  deadband: " << deadband_ << std::endl;
    std::cout << "  hysteresis: " << hysteresis_ << std::endl;
    std::cout << "}" << std::endl;
}
