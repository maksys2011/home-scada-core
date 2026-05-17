#include <istream>
#include "MqttActuatorConfig.hpp"
#include "utils.hpp"

MqttActuatorConfig::MqttActuatorConfig(
    const std::string &client_id, 
    ActuatorType type, 
    bool defaultStatus, 
    CommandType cmd,
    ActuatorConnectionType connection_type,
    const std::string &id, 
    const std::string &broker, 
    const std::string &topic, 
    int expectedIndex, 
    const std::string &transport) 
    :
    BaseActuatorConfig(
        client_id, 
        type, 
        defaultStatus, 
        cmd, 
        connection_type,
        expectedIndex,
        id), 
    broker_(broker), 
    topic_(topic), 
    transport_(transport)
{}

void MqttActuatorConfig::fromJson(const json &j)
{
    client_id_ = scada::utils::check_the_key<std::string>(j, "client_id");
    type_ = ParseActuatorType(scada::utils::check_the_key<std::string>(j, "type"));
    cmd_ = ParceCommandType(scada::utils::check_the_key<std::string>(j, "commandType"));
    connection_type_ =  ParceActuatorConnectionType(scada::utils::check_the_key<std::string>(j, "transport"));
    id_ = scada::utils::check_the_key<std::string>(j ,"id");
    broker_ = scada::utils::check_the_key<std::string>(j, "broker");
    topic_ = scada::utils::check_the_key<std::string>(j, "topic");
    std::string indexCmd = scada::utils::check_the_key<std::string>(j, "expectedIndex");
    expectedIndex_ = scada::utils::getTeamIndex(indexCmd);
    transport_ = scada::utils::check_the_key<std::string>(j, "transport");
}

void MqttActuatorConfig::fromJson(const std::filesystem::path &path)
{
    std::ifstream file = scada::utils::create_json_ifstream(path);
    json j;
    file >> j;
    fromJson(j);
}

bool MqttActuatorConfig::validate() const
{
    return true;
}

void MqttActuatorConfig::printInfo() const
{
    std::cout << "mqtt actuator config obj" << std::endl;
}
