#include <gtest/gtest.h>
#include <filesystem>
#include <nlohmann/json.hpp>
#include "SensorConfig.hpp"
using json = nlohmann::json;

static json makeJsonSensorConfig()
{
    json j = {
        {"id_" , "10001"},
        {"name_" , "temperature_kitchen"},
        {"type_" , "Analog"},
        {"unit" , "celsius"},
        {"physicalMin_" , 0.0},
        {"physicalMax_" , 100.0},
        {"noiseEpsilon_" , 0.5},
        {"staleTimeout_" , 500},
        {"warnHigh_", 50.5},
        {"warnLow_" , 10},
        {"alarmHigh_" , 95.0},
        {"alarmLow_" , 5.0},
        {"deadband_" , 0.5},
        {"hysteresis_" , 0.2},
        {"enabled_" , false},
        {"source_id" , "500"}
    };
    return j;
}

TEST(SensorConfigTest, Init)
{
    SensorConfig cfg;
    auto j = makeJsonSensorConfig();
    cfg.fromJson(j);
    EXPECT_EQ(cfg.getId(), "10001");
    EXPECT_EQ(cfg.getName(), "temperature_kitchen");
    EXPECT_EQ(cfg.getType(), SensorType::Analog);
    EXPECT_EQ(cfg.getSensorUnit(), SensorUnit::CELSIUS);
    EXPECT_DOUBLE_EQ(cfg.getPhysicalMin(), 0.0);
    EXPECT_DOUBLE_EQ(cfg.getphysicalMax(), 100.0);
    EXPECT_DOUBLE_EQ(cfg.getNoiseEpsilon(), 0.5);
    EXPECT_DOUBLE_EQ(cfg.getWarnHigh(), 50.5);
    EXPECT_DOUBLE_EQ(cfg.getWarnLow(), 10.0);
    EXPECT_DOUBLE_EQ(cfg.getAlarmHigh(), 95.0);
    EXPECT_DOUBLE_EQ(cfg.getAlarmLow(), 5.0);
    EXPECT_DOUBLE_EQ(cfg.deadband(), 0.5);
    EXPECT_DOUBLE_EQ(cfg.hysteresis(), 0.2);
    EXPECT_EQ(cfg.getSourceId(), "500");
}

TEST(SensorConfigTest, FileNotFound)
{
    std::filesystem::path path = "non_existent_file.json";
    SensorConfig cfg;
    EXPECT_THROW(cfg.fromJson(path), std::runtime_error);
}

TEST(SensorConfigTest, EdgeCases)
{
    auto j = makeJsonSensorConfig();
    SensorConfig cfg;
    cfg.fromJson(j);
    EXPECT_TRUE(cfg.validate());
}

TEST(SensorConfigTest, InvalidEdgeCase)
{
    auto j = makeJsonSensorConfig();
    j["alarmLow_"] = 11.0;
    SensorConfig cfg;
    cfg.fromJson(j);
    EXPECT_FALSE(cfg.validate());
}

TEST(SensorConfigTest, MissingIdField)
{
    auto j = makeJsonSensorConfig();
    j.erase("id_");
    SensorConfig cfg;
    EXPECT_THROW(cfg.fromJson(j), std::runtime_error);
}

TEST(SensorConfigTest, TypeMismatch)
{
    auto j = makeJsonSensorConfig();
    j["id_"] = true;
    SensorConfig cfg;
    EXPECT_THROW(cfg.fromJson(j), json::exception);
}


