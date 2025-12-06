#include <iostream>
#include <fstream>
#include <vector>
#include <nlohmann/json.hpp>
#include "SensorConfig.h"
using json = nlohmann::json;

int main()
{
    std::string file = "../config.json";
    SensorConfig s;
    s.fromJson(file);
    s.print();
    



    return 0;
}