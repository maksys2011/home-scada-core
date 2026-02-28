#pragma once
#include <nlohmann/json.hpp>
#include <string>
#include <filesystem>
#include <iostream>
using json = nlohmann::json;

namespace scada::utils
{
    template<typename T>
    T check_the_key(const json& j, const std::string& key){
        auto it = j.find(key);
        if(it == j.end()){
            throw std::runtime_error(
                "there is no required key= " + key
            );
        }
        return it->get<T>();
    };

    std::ifstream create_json_ifstream(const std::filesystem::path& path);

    void validateIpv4(const std::string& ip, const std::string& nameDevice);

    void validatePort(int port, const std::string& nameDevice);

    void validateSlaveId(int slaveId, const std::string& nameDevice);
}