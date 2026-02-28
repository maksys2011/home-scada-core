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

void scada::utils::validateIpv4(const std::string &ip, const std::string& nameDevice)
{
    if(ip.empty()){
        throw std::runtime_error(std::string(nameDevice + " : ip address cannot be empty"));
    }

    std::stringstream str(ip);
    std::string segment;
    int count = 0;

    while(std::getline(str, segment, '.')){
            
        if(segment.empty() || segment.length() > 3){
           throw std::runtime_error(
                std::string(nameDevice + " : ip segment cannot exceed 3 characters "
            + segment + " -> " + ip)); 
        }
        
        for(char ch : segment){
            if(!std::isdigit(ch)){
                throw std::runtime_error(
                    std::string(nameDevice + " : ip address can only contain digits (0-9) " 
                        + segment + " -> " + ip));
            }
        }
        
        int value = std::stoi(segment);
        
        if(value >= 0 && value <= 255){
            count++;
        }else{
            throw std::runtime_error(
                std::string(nameDevice + " : ip segment value must be between 0 and 255 " 
                    + segment + " -> " + ip));
        }
    }

    if(count < 4 || count > 4){
            throw std::runtime_error(nameDevice + " : ip address must contain 4 segments  -> " + ip);
        }
}

void scada::utils::validatePort(int port, const std::string &nameDevice)
{
    if(port < 0 || port > 65535){
        throw std::runtime_error(
            nameDevice + " : port must be in range 0-65535 " + std::to_string(port)
        );
    }
}

void scada::utils::validateSlaveId(int slaveId, const std::string &nameDevice)
{
    if(slaveId < 0 || slaveId > 248){
        throw std::runtime_error(
            nameDevice + " : slave id must be in rande 0-248 " 
            + std::to_string(slaveId)
        );
    }
}
