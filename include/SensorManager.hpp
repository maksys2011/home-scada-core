#pragma once

#include <unordered_map>
#include <string>

class Sensor;

class SensorManager{
public:

    bool addSensor(const std::string& id, Sensor* sensor);

    bool updateValue(const std::string& id, double value);

private:

    std::unordered_map<std::string, Sensor*> sensors_;
};