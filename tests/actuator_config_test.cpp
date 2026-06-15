#include <gtest/gtest.h>
#include <filesystem>
#include "ActuatorConfig.hpp"
#include "Enum.hpp"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

static json makeJsonActuatorConfig(){
    json j = {
        {"actuator_type" , "split_system"},
        {"location" , "kitchen"},
        {"client_id" , "100"},
        {"startAddress" , 0},
        {"id" , "35001"},
        {"type" , "AnalogOut"},
        {"minValue" , 0.0},
        {"maxValue" ,  100.0},
        {"commandType" , "Turn"},
        {"expectedIndex" , "bool"},
        {"transport" , "Modbus"}
    };
    return j;
}

// TEST 1

TEST(ActuatorConfigTest, Init)
{
    ActuatorConfig cfg;
    cfg.fromJson(makeJsonActuatorConfig());

    EXPECT_EQ(cfg.getIdClient(), "100");
    EXPECT_EQ(cfg.getStartAddress(), 0);
    EXPECT_EQ(cfg.getId(), "35001");
    EXPECT_EQ(cfg.getName(), "split_system");
    EXPECT_EQ(cfg.getType(), ActuatorType::AnalogOut);
    EXPECT_EQ(cfg.getExpectedIndex(), 0);
    EXPECT_EQ(cfg.getCmd(), CommandType::Turn);
    EXPECT_EQ(cfg.getTransport(), "Modbus");
}

// TEST 2

TEST(ActuatorConfigTest, Validate50_50)
{
    auto j = makeJsonActuatorConfig();
    j["minValue"] =  50.0;
    j["maxValue"] =  50.0;

    ActuatorConfig cfg;
    cfg.fromJson(j);

    EXPECT_TRUE(cfg.validate());
}

// TEST 3

TEST(ActuatorConfigTest, Validate100_50)
{
    auto j = makeJsonActuatorConfig();
    j["minValue"] =  100.0;
    j["maxValue"] =  50.0;

    ActuatorConfig cfg;
    cfg.fromJson(j);

    EXPECT_FALSE(cfg.validate());
}





