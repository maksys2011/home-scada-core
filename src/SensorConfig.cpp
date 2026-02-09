#include <SensorConfig.hpp>
#include <iostream>
#include <fstream>
#include <cmath>
using json = nlohmann::json;

SensorConfig::SensorConfig(
    const std::string &id,
    const std::string &name,
    SensorType type,

    double physicalMin,
    double physicalMax,
    double noiseEpsilon,
    std::chrono::seconds staleTimeout,

    double warnHigh,
    double warnLow,
    double alarmHigh,
    double alarmLow,

    double deadband,
    double hysteresis,

    bool enabled): 

    id_(id),
    name_(name),
    type_(type),

    physicalMin_(physicalMin),
    physicalMax_(physicalMax),
    noiseEpsilon_(noiseEpsilon),
    staleTimeout_(staleTimeout),

    warnHigh_(warnHigh),
    warnLow_(warnLow),
    alarmHigh_(alarmHigh),
    alarmLow_(alarmLow),

    deadband_(deadband),
    hysteresis_(hysteresis),

    enabled_(enabled)
{}


void SensorConfig::fromJson(const json &j)
{
    if(j.contains("id_")) {
        id_ = j.at("id_").get<std::string>();
    }else{
        throw std::runtime_error(
            "there is no required key= id_"
        );
    }

    if(j.contains("name_")){
        name_ = j.at("name_").get<std::string>();
    }else{
        throw std::runtime_error(
            "there is no required key= name_"
        );  
    }

    if(j.contains("type_")){
        type_ = ParseSensorType(j.at("type_").get<std::string>());
    }else{
        throw std::runtime_error(
            "there is no required key= type_"
        ); 
    }

    if(j.contains("physicalMin_")){
        physicalMin_ = j.at("physicalMin_").get<double>();
    }else{
        throw std::runtime_error(
            "there is no required key= physicalMin_"
        );
    }

    if(j.contains("physicalMax_")){
        physicalMax_ = j.at("physicalMax_").get<double>();
    }else{
        throw std::runtime_error(
            "there is no required key= physicalMax_"
        );
    }

    if(j.contains("noiseEpsilon_")){
        noiseEpsilon_ = j.at("noiseEpsilon_").get<double>();
    }else{
        throw std::runtime_error(
            "there is no required key= noiseEpsilon_"
        );
    }

    if(j.contains("staleTimeout_")){
        staleTimeout_ = std::chrono::seconds(j.at("staleTimeout_").get<int>());
    }else{
        staleTimeout_ = std::chrono::seconds(500);
    }

    if(j.contains("warnHigh_")){
        warnHigh_ = j.at("warnHigh_").get<double>();
    }else{
        warnHigh_ = physicalMax_;
    }

    if(j.contains("warnLow_")){
        warnLow_ = j.at("warnLow_").get<double>();
    }else{
        warnLow_ = physicalMin_;
    }

    if(j.contains("alarmHigh_")){
        alarmHigh_ = j.at("alarmHigh_").get<double>();
    }else{
        alarmHigh_ = physicalMax_;
    }

    if(j.contains("alarmLow_")){
        alarmLow_ = j.at("alarmLow_").get<double>();
    }else{
        alarmLow_ = physicalMin_;
    }

    if(j.contains("deadband_")){
       deadband_ = j.at("deadband_").get<double>(); 
    }else{
        deadband_ = noiseEpsilon_;
    }

    if(j.contains("hysteresis_")){
       hysteresis_ = j.at("hysteresis_").get<double>(); 
    }else{
        hysteresis_ = 0.0;
    }  

    if(j.contains("enabled_")){
        enabled_ = j.at("enabled_").get<bool>();
    }else{
        enabled_ = true;
    }
}

//void SensorConfig::fromJson(const std::string &path)
void SensorConfig::fromJson(const std::filesystem::path& path)
{
    std::ifstream file(path);
    if(!file){
        throw std::runtime_error("cannot open config file" + path.string());
    }
    json j;
    file >> j;
    fromJson(j);
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
    return  std::isfinite(v);
}

void SensorConfig::print() const
{
    std::cout << "SensorConfig {" << std::endl;
    std::cout << "  id: " << id_ << std::endl;
    std::cout << "  name: " << name_ << std::endl;
    std::cout << "  type: ";
    std::cout << SensorTypeToString(type_) << std::endl;
    std::cout << "  physicalMin: " << physicalMin_ << std::endl;
    std::cout << "  physicalMax: " << physicalMax_ << std::endl;
    std::cout << "  noiseEpsilon: " << noiseEpsilon_ << std::endl;
    std::cout << "  warnHigh: " << warnHigh_ << std::endl;
    std::cout << "  warnLow: " << warnLow_ << std::endl;
    std::cout << "  alarmHigh: " << alarmHigh_ << std::endl;
    std::cout << "  alarmLow: " << alarmLow_ << std::endl;
    std::cout << "  deadband: " << deadband_ << std::endl;
    std::cout << "  hysteresis: " << hysteresis_ << std::endl;
    std::cout << "  current state: " << (enabled_? "ON" : "OFF") << std::endl;
    std::cout << "}" << std::endl;
}
