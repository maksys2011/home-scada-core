#include <iostream>
#include <map>
#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>
#include "ArchiveReport.hpp"


static std::string formatTime(std::time_t ts)
{
    std::tm tm{};
    localtime_r(&ts, &tm);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H-%M-%S");

    return oss.str();
}

void ArchiveRepotr::printSummary(const std::vector<ArchiveRecord> &records)
{
    if(records.empty()) {
        std::cout << "No data\n";
        return;
    }

    std::map<std::string, std::vector<ArchiveRecord>> grouped;

    for(const auto& rec : records){
        grouped[rec.sensorId_].push_back(rec);
    }

    for(const auto& [sensorId, list] : grouped){
        
        const std::string& name = list.front().sensorName_;

        double min_value = list.front().value_;
        double max_value = list.front().value_;
        double sum = 0.0;

        std::time_t firstTs = list.front().timestamp_;
        std::time_t lastTs = list.front().timestamp_;

        for(auto& it : list){
            sum += it.value_;

            if(it.value_ < min_value) min_value = it.value_;
            if(it.value_ > max_value) max_value = it.value_;

            if(it.timestamp_ < firstTs) firstTs = it.timestamp_;
            if(it.timestamp_ > lastTs) lastTs = it.timestamp_;
        }

        double avg = sum / records.size();

        std::cout <<"================================================\n";
        std::cout <<"Sensor Id   : " << sensorId << "\n";
        std::cout <<"Sensor Name : " << name << "\n\n";
        std::cout <<"Records     : " << records.size() << "\n";
        std::cout <<"Min value   : " << min_value << "\n";
        std::cout <<"Max value   : " << max_value << "\n";
        std::cout <<"Average     : " << avg << "\n\n";
        std::cout <<"Period      : " << "\n" << 
                      "     Beginning   : " << formatTime(firstTs) << "\n" 
                    <<"     End         : " << formatTime(lastTs) << "\n";
        std::cout <<"================================================\n";
    }
}