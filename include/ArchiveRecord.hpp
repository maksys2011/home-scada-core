#pragma once
#include <string>
#include <ctime>
#include "Enum.hpp"

class ArchiveRecord
{
public:
    ArchiveRecord(std::time_t t, 
                    std::string& sId, 
                    std::string& sName,
                    double value,
                    const State st):
        timestamp_(t),
        sensorId_(sId),
        sensorName_(sName),
        value_(value),
        state_(st)      
{}            
    std::time_t timestamp_;
    std::string sensorId_;
    std::string sensorName_;
    double value_;
    State state_;

};