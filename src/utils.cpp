#include "utils.hpp"
#include <fstream>

std::ifstream scada::utils::create_json_ifstream(const std::filesystem::path &path)
{
    std::ifstream file(path);
    
    if(!file.is_open()){
       if(!file){
        throw std::runtime_error(
            "cannot open config file" + path.string());
        } 
    }
    return file;
}

bool scada::utils::validateIpV4(const std::string& ip)
{
    if(ip.empty()) return false;

    std::stringstream str(ip);
    std::string segment;
    int count = 0;

    while(std::getline(str, segment, '.')){
            
        if(segment.empty() || segment.length() > 3) return false;
        
        for(char ch : segment){
            if(!std::isdigit(ch)) return false;
        }
        
        int value = std::stoi(segment);
        
        if(value < 0 || value > 255) return false;

            count++;
        }
    return count == 4;
}

bool scada::utils::validatePort(const int port)
{
    return port > 0 && port < 65535;
}


