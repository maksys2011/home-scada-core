#include "SensorManager.hpp"
#include "Sensor.hpp"

bool SensorManager::addSensor(const std::string &id, Sensor *sensor)
{
    if(!sensor) return false;
    return sensors_.emplace(id, sensor).second;
}

void SensorManager::tick()
{
    for(auto& [id, sensor] : sensors_){
        sensor->update();
    }
}


