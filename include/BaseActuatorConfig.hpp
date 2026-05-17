#pragma once
#include <string>
#include <Enum.hpp>
#include <nlohmann/json.hpp>
#include <filesystem>

using json = nlohmann::json;

class BaseActuatorConfig
{
protected:
    std::string client_id_{};
    ActuatorType type_ = ActuatorType::AnalogOut;
    bool defaultStatus_ = false;
    CommandType cmd_ = CommandType::Unknown;
    ActuatorConnectionType connection_type_ = ActuatorConnectionType::Unknown;
    int expectedIndex_ = 0;
    std::string id_{};

public:
    BaseActuatorConfig() = default;
    BaseActuatorConfig(const std::string& client_id, 
        ActuatorType type,
        bool defaultStatus,
        CommandType cmd,
        ActuatorConnectionType connection_type,
        int expectedIndex,
        const std::string& id)
        :
        client_id_(client_id), 
        defaultStatus_(defaultStatus), 
        type_(type), 
        cmd_(cmd),
        connection_type_(connection_type),
        expectedIndex_(expectedIndex),
        id_(id)
    {}
    virtual ~BaseActuatorConfig() = default;

    virtual void fromJson(const json& j) = 0;
    virtual void fromJson(const std::filesystem::path& path) = 0;
    virtual bool validate() const = 0;
    virtual void printInfo() const = 0;

    const std::string& getClient_id() const { return client_id_; };
    ActuatorType getActuatorType() const { return type_; };
    const bool getDefaultStatus() const { return defaultStatus_; };
    CommandType getCmd() const { return cmd_; };
    ActuatorConnectionType getConnectionType() const { return connection_type_; };
    const int getExpectedIndex() const { return expectedIndex_; };
    const std::string& getIdActuator() { return id_; };
};

