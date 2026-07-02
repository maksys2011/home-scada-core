#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <nlohmann/json.hpp>
#include <limits>
#include <cmath>
#include "SensorState.hpp"
#include "SensorConfig.hpp"
using json = nlohmann::json;

json makeJsonSensorConfig()
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
        {"warnHigh_" , 50.5},
        {"warnLow_" , 10},
        {"alarmHigh_", 95.0},
        {"alarmLow_", 5.0},
        {"deadband_" , 0.5},
        {"hysteresis_" , 0.2},
        {"enabled_" , false},
        {"source_id" , "500"}
    };
    return j;
}

TEST(SensorStateTest, InfInput)
{
    SensorConfig cfg;
    EXPECT_NO_THROW(cfg.fromJson(makeJsonSensorConfig()));

    double infiniteSample = std::numeric_limits<double>::infinity();
    SensorState state(cfg);

    EXPECT_TRUE(state.classifyDataQuality(infiniteSample) == State::INVALID);
}

TEST(SensorStateTest, ClassifyNoiseEpsilonValue)
{
    double raw = 20;
    double next_raw = 20.1;
    
    SensorConfig cfg;
    EXPECT_NO_FATAL_FAILURE(cfg.fromJson(makeJsonSensorConfig()));

    SensorState state(cfg);
    state.processValue(raw);

    EXPECT_TRUE(*state.lastValue() == raw);
    EXPECT_TRUE(state.status() == State::OK);

    state.processValue(next_raw);

    EXPECT_TRUE(*state.lastValue() == raw);
    EXPECT_TRUE(state.status() == State::OK);
}

TEST(SensorStateTest, StatusReturnOk)
{
    double raw = 0;

    SensorConfig cfg;
    EXPECT_NO_THROW(cfg.fromJson(makeJsonSensorConfig()));

    SensorState state(cfg);

    state.classifyAlarmState(raw);

    state.processValue(raw);

    EXPECT_EQ(state.status(), State::OK);
}

TEST(SensorStateTest, StatusReturnWarn)
{
    double raw = 9;
    double next_raw = 8;

    SensorConfig cfg;
    EXPECT_NO_THROW(cfg.fromJson(makeJsonSensorConfig()));

    SensorState state(cfg);
    state.processValue(raw);

    EXPECT_EQ(state.status(), State::OK);

    state.processValue(next_raw);

    EXPECT_EQ(state.status(), State::WARN);

    state.processValue(next_raw);

    EXPECT_EQ(state.status(), State::WARN);
}

TEST(SensorStateTest, StatusReturnAlarm)
{
    double raw = 96;
    double next_raw = 97;
    double after_next = 98;

    SensorConfig cfg;
    EXPECT_NO_THROW(cfg.fromJson(makeJsonSensorConfig()));

    SensorState state(cfg);
    state.processValue(raw);

    EXPECT_EQ(state.status(), State::OK);

    state.processValue(next_raw);

    EXPECT_EQ(state.status(), State::ALARM);

    state.processValue(after_next);

    EXPECT_EQ(state.status(), State::ALARM);
}






