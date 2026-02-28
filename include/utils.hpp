#pragma once
#include <nlohmann/json.hpp>
#include <string>
#include <filesystem>
#include <iostream>
#include <memory>
#include <vector>
#include <fstream>

#include "RuleConfig.hpp"
#include "RuleConfigLight.hpp"
#include "RuleThermostatConfig.hpp"

using json = nlohmann::json;

namespace scada
{
    namespace utils
    {    
    
        template<typename T>
        T check_the_key(const json& j, const std::string& key){
            auto it = j.find(key);
            if(it == j.end()){
                throw std::runtime_error("there is no required key= " + key);
        }
        return it->get<T>();
        };

        std::ifstream create_json_ifstream(const std::filesystem::path& path);

        void validateIpv4(const std::string& ip, const std::string& nameDevice);

        void validatePort(int port, const std::string& nameDevice);

        void validateSlaveId(int slaveId, const std::string& nameDevice);

    }

    namespace factory
    {  
        std::unique_ptr<RuleConfig> create(const json& j);

        template<typename T>
        std::vector<T> loadHierarchy(const std::string& msg1, const std::string& msg2,  const std::filesystem::path& pathFile)
        {
    
            std::vector<T> result;

            std::ifstream file(pathFile);
            if(!file.is_open()){
                throw std::runtime_error(std::string(msg1 + pathFile.string()));
            }

            json j;
            file >> j;

            if(j.is_array()){
                for(const auto& item : j){
                    T cfg;
                    cfg.fromJson(item);
                    result.push_back(std::move(cfg));
                }
            }else if(j.is_object()){
                T cfg;
                cfg.fromJson(j);
                result.push_back(std::move(cfg));
            }else{
                throw std::runtime_error(msg2);
            }

            return result;
        }

        std::vector<std::unique_ptr<RuleConfig>> loadPolymorphic(const std::string& msg1, const std::string& msg2, const std::filesystem::path& pathFile);
    }

}




