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

void scada::utils::validateId(const std::string &id, const std::string &nameDavice)
{
    if(id.empty()){
        throw std::runtime_error(nameDavice + ": id cannot be empty");
    }
}

int scada::utils::getTeamIndex(const std::string indexCmd)
{
    if(indexCmd == "bool") return 0;
    else if(indexCmd == "int") return 1;
    else if(indexCmd == "double") return 2;
    else if(indexCmd == "string") return 3;
    else return -1;
    return 0;
}

std::unique_ptr<RuleConfig> scada::factory::create(const json& j)
{
    std::string type = j.at("name_rule").get<std::string>();

    if(type == "lighting rules"){
        auto cfg = std::make_unique<RuleConfigLight>();
        cfg->fromJson(j);
        return cfg;
    }else if(type == "temperature rules"){
        auto cfg = std::make_unique<RuleThermostatConfig>();
        cfg->fromJson(j);
        return cfg;
    }else{
        throw std::runtime_error("Unknown rule type");
    }
}

std::vector<std::unique_ptr<RuleConfig>> scada::factory::loadPolymorphic(
    const std::string& msg1, 
    const std::string& msg2, 
    const std::filesystem::path& pathFile)
{
            
    std::vector<std::unique_ptr<RuleConfig>> result;

    std::ifstream file = scada::utils::create_json_ifstream(pathFile);
    json j;
    file >> j;

    if(j.is_array()){
        for(const auto& item : j){
            result.push_back(scada::factory::create(item));
        }
    }else if(j.is_object()){
            result.push_back(scada::factory::create(j));
    }else{
            throw std::runtime_error(msg2);
    }
    
    return result;
}

std::unique_ptr<SourceConfig> scada::source::create(const json &j)
{
    std::string typeSource = j.at("type_source").get<std::string>();
    if(typeSource == "Modbus"){
        auto cfg = std::make_unique<ModbusSourceConfig>();
        cfg->fromJson(j);
        return cfg;
    }else if(typeSource == "Mqtt"){
        auto cfg = std::make_unique<MqttSourceConfig>();
        cfg->fromJson(j);
        return cfg;
    }else{
        throw std::runtime_error(
            "Unknown source config type");
    }
}

std::vector<std::unique_ptr<SourceConfig>> scada::source::loadPolymorphic(
    const std::string& msg1, 
    const std::string& msg2, 
    const std::filesystem::path& pathFile)
{
    std::vector<std::unique_ptr<SourceConfig>> configs;

    std::ifstream file = scada::utils::create_json_ifstream(pathFile);
    json j;
    file >> j;

    if(j.is_array()){
        for(const auto& item : j){
            configs.push_back(scada::source::create(item));
        }
    }else if(j.is_object()){
        configs.push_back(scada::source::create(j));
    }else{
        throw std::runtime_error(msg2);
    }

    return configs;
}
