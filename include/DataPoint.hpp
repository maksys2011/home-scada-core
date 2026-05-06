#pragma once
#include <chrono>

struct DataPoint
{
    double value;
    std::chrono::system_clock::time_point timestamp;
};