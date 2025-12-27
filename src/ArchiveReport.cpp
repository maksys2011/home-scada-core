#include <iostream>
#include <map>
#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <fstream>
#include "ArchiveReport.hpp"


static std::string formatTime(std::time_t ts)
{
    std::tm tm{};
    localtime_r(&ts, &tm);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H-%M-%S");

    return oss.str();
}

static void writeSummary(std::ostream& out, 
                const std::vector<ArchiveRecord>& records)
{
    if(records.empty()){
        out << "Archove is empty \n";
        return;
    }

    const auto& first = records.front();
    const auto& last = records.back();

    double min_value = records.front().value_;
    double max_value = records.front().value_;
    double sum = 0.0;

    int okCount = 0;
    int warnCount = 0;
    int alarmCount = 0;

    for(const auto& it : records){
        if(it.value_ < min_value) min_value = it.value_;
        if(it.value_ > max_value) max_value = it.value_;

        sum += it.value_;

        if(it.state_ == State::OK) okCount++;
        else if(it.state_ == State::WARN) warnCount++;
        else if(it.state_ == State::ALARM) alarmCount++;

    }

    double average = sum / records.size();

    out << "============================================\n";
    out << "Sensor Id     : " << first.sensorId_ << "\n";
    out << "Sensor Name   : " << first.sensorName_ << "\n";

    out << "Records       : " << records.size() << "\n";
    out << "Min value     : " << min_value << "\n";
    out << "Max value     : " << max_value << "\n";
    out << "Average       : " << average << "\n";

    out << "States        : \n";
    out << " OK    : " << okCount << "\n";
    out << " WARN  : " << warnCount << "\n";
    out << " ALARM : " << alarmCount << "\n";

    out << "Last value    : " << last.value_ << " " << StateToString(last.state_) << " \n";
    
    out << "Period : \n";
    out << "Beginnig : " << formatTime(first.timestamp_) << "\n";
    out << "End      : " << formatTime(last.timestamp_) << "\n";
    out << "============================================\n";
}

void ArchiveReport::printSummary(const std::vector<ArchiveRecord> &records)
{
    writeSummary(std::cout, records);  
}

void ArchiveReport::writeSummaryToFile(const std::vector<ArchiveRecord> &records, const std::string& filePath)
{
    std::ofstream file(filePath);

    if(!file.is_open()){
        std::cerr << "Failed to open report file: " << filePath << "\n";
        return;
    }

    writeSummary(file, records);

}




