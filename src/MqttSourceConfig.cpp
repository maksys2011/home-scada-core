#include "MqttSourceConfig.hpp"
#include <fstream>
#include <iostream>

MqttSourceConfig::MqttSourceConfig(
    std::string &name, 
    std::string &sourceId, 
    std::string &broker, 
    std::string &clientId, 
    std::string &topic, 
    int qos)
    :
    name_(name),
    sourceId_(sourceId),
    broker_(broker),
    clientId_(clientId),
    topic_(topic),
    qos_(qos)
{}

void MqttSourceConfig::fromJson(const json &j)
{
    auto new_name = scada::utils::check_the_key<std::string>(j, "name");
    auto new_sourceId = scada::utils::check_the_key<std::string>(j, "source_id");
    auto new_broker = scada::utils::check_the_key<std::string>(j, "broker");
    auto new_clientId = scada::utils::check_the_key<std::string>(j, "client_id");
    auto new_topic = scada::utils::check_the_key<std::string>(j, "topic");
    int new_gos = scada::utils::check_the_key<int>(j, "qos");

    validate();

    name_ = std::move(new_name);
    sourceId_ = std::move(new_sourceId);
    broker_ = std::move(new_broker);
    clientId_ = std::move(new_clientId);
    topic_ = std::move(new_topic);
    qos_ = new_gos;
}

void MqttSourceConfig::fromJson(const std::filesystem::path &path)
{
    std::ifstream file = scada::utils::create_json_ifstream(path);
    json j;
    file >> j;
    fromJson(j);
}

void MqttSourceConfig::print()
{
    std::cout << "MQTT Client config source:" << std::endl;
    std::cout << "name= " << name_ << std::endl;
    std::cout << "sourceId= " << sourceId_ << std::endl;
    std::cout << "broker= " << broker_ << std::endl;
    std::cout << "clientId= " << clientId_ << std::endl;
    std::cout << "topic= " << topic_ << std::endl;
    std::cout << "gos= " << qos_ << std::endl; 
}

void MqttSourceConfig::validate()
{
}
