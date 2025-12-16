#pragma once
#include <string>
#include <Enum.hpp>
#include <fstream>
#include <chrono>

class Archive
{
public:

    explicit Archive(const std::string& filePath);
    Archive (const Archive&) = delete;
    Archive& operator=(const Archive&) = delete;
    
    ~Archive();

    void appendArchive(
        
        const std::string& Id,
        const std::string& nameSensor,
        double value,
        State state

    );

private:

    std::ofstream file_;
    
};