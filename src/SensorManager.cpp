#include "SensorManager.hpp"
#include "Sensor.hpp"

bool SensorManager::addSensor(const std::string &id, Sensor *sensor)
{
    if(!sensor) return false;
    return sensors_.emplace(id, sensor).second;
}

bool SensorManager::updateValue(const std::string &id, double value)
{
    auto it = sensors_.find(id);
    if(it == sensors_.end()){
        return false;
    }

    it->second->updateValue(value);
    return true;
}
