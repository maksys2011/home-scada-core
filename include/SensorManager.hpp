#pragma once

#include <unordered_map>
#include <string>

class Sensor;

class SensorManager{
public:

    bool addSensor(const std::string& id, Sensor* sensor);

    void tick();

private:

    std::unordered_map<std::string, Sensor*> sensors_;
    

};