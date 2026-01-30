#include "Archive.hpp"
#include <iostream>
#include <chrono>
#include <iomanip>
#include <filesystem>

Archive::Archive(const std::string& filePath)
    : Archive::Archive(std::filesystem::path(filePath))
{}

Archive::Archive(const std::filesystem::path& filePath)
{
    file_.open(filePath, std::ios::app);
    if(!file_.is_open()){
        throw std::runtime_error(
            std::string("Archive cannot open file: ") +
            filePath.string()
        );
    }
}

Archive::~Archive()
{   
    if(file_.is_open()){
        file_.close();
    }
}

void Archive::appendArchive(const std::string &Id, const std::string &nameSensor, double value, State state)
{
    if(!file_.is_open()) return;

    auto now = std::chrono::system_clock::now();
    auto t = std::chrono::system_clock::to_time_t(now);
    file_ 
        << t << ';'
        << Id << ';'
        << nameSensor << ';'
        << value << ';'
        << StateToString(state) 
        << '\n';
}
