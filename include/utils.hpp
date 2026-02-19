#pragma once
#include <nlohmann/json.hpp>
#include <string>
#include <filesystem>
using json = nlohmann::json;

namespace scada::utils
{
    template<typename T>
    T check_the_key(const json& j,const std::string& key){
        auto it = j.find(key);
        if(it == j.end()){
            throw std::runtime_error(
                "there is no required key=" + key
            );
        }
        return it->get<T>();
    };

    std::ifstream create_json_ifstream(const std::filesystem::path& path);
}