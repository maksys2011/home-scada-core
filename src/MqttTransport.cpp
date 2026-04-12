#include "MqttTransport.hpp"

bool MqttTransport::send(const std::string& target, const TransportValue& val)
{
    std::string payLoad{};

    if(const int* cmd = std::get_if<int>(&val))
    {
        payLoad = std::to_string(*cmd);

    }else if(const bool* cmd = std::get_if<bool>(&val))
    {
        payLoad = std::to_string(*cmd);

    }else if(const double* cmd = std::get_if<double>(&val))
    {
        payLoad = std::to_string(*cmd);

    }else if(const std::string *cmd = std::get_if<std::string>(&val))
    {
        payLoad = *cmd;
        
    }else
    {
        std::cerr << "MQTT Send failed: Unknown type in variant" << std::endl;
        return false;
    }

    return client_.publishCommand(target, payLoad);
}