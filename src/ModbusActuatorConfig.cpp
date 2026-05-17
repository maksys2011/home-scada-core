#include <istream>
#include "ModbusActuatorConfig.hpp"
#include "utils.hpp"

ModbusActuatorConfig::ModbusActuatorConfig(
    const std::string &client_id, 
    ActuatorType type, 
    bool defaultStatus, 
    CommandType cmd,
    ActuatorConnectionType connection_type, 
    int startAddress, 
    const std::string &id, 
    double minValue, 
    double maxValue, 
    bool inverted, 
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
    startAddress_(startAddress),
    minValue_(minValue),
    maxValue_(maxValue),
    inverted_(inverted),
    transport_(transport)
{}

void ModbusActuatorConfig::fromJson(const json &j)
{
    client_id_ = scada::utils::check_the_key<std::string>(j, "client_id");
    type_ = ParseActuatorType(scada::utils::check_the_key<std::string>(j, "type"));
    cmd_ = ParceCommandType(scada::utils::check_the_key<std::string>(j, "commandType"));
    connection_type_ =  ParceActuatorConnectionType(scada::utils::check_the_key<std::string>(j, "transport"));
    id_ = scada::utils::check_the_key<std::string>(j, "id");
    startAddress_ = scada::utils::check_the_key<int>(j, "startAddress");
    type_ = ParseActuatorType(scada::utils::check_the_key<std::string>(j, "type"));
    minValue_ = scada::utils::check_the_key<double>(j, "minValue");
    maxValue_ = scada::utils::check_the_key<double>(j, "maxValue");
    std::string indexCmd = scada::utils::check_the_key<std::string>(j, "expectedIndex");
    expectedIndex_ = scada::utils::getTeamIndex(indexCmd);
    transport_ = scada::utils::check_the_key<std::string>(j, "transport");  
}

void ModbusActuatorConfig::fromJson(const std::filesystem::path &path)
{
    std::ifstream file = scada::utils::create_json_ifstream(path);
    json j;
    file >> j;
    fromJson(j);
}

bool ModbusActuatorConfig::validate() const
{
    return minValue_ <= maxValue_;
}

void ModbusActuatorConfig::printInfo() const
{
    std::cout << "modbus actuator config obj" << std::endl;
}
