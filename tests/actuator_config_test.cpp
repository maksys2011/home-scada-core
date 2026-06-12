#include <gtest/gtest.h>
#include <filesystem>
#include "ActuatorConfig.hpp"
#include "Enum.hpp"
#include <nlohmann/json.hpp>

TEST(ActuatorConfigTest, StoresBasicFields)
{
    std::filesystem::path path = "../configs/actuators/test.json";
    ActuatorConfig cfg;
    cfg.fromJson(path);


    EXPECT_EQ(cfg.getIdClient(), "100");
    EXPECT_EQ(cfg.getStartAddress(), 0);
    EXPECT_EQ(cfg.getId(), "35001");
    EXPECT_EQ(cfg.getName(), "split_system");
    EXPECT_EQ(cfg.getType(), ActuatorType::AnalogOut);
    EXPECT_EQ(cfg.getExpectedIndex(), 0);
    EXPECT_EQ(cfg.getCmd(), CommandType::Turn);
    EXPECT_EQ(cfg.getTransport(), "Modbus");
}
