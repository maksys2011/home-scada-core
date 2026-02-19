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