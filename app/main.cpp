#include <iostream>
#include <fstream>
#include <vector>
#include <nlohmann/json.hpp>
#include <SensorConfig.h>
using json = nlohmann::json;

int main()
{
    SensorConfig sensor("config.json");
    sensor.print();


    return 0;
}