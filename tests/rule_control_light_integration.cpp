#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include <atomic>
#include "RuleControlLight.hpp"
#include "RuleConfigLight.hpp"
#include "scada_core_testing_utils.hpp"
#include "RuleControlLight.hpp"
using json = nlohmann::json;

static json makeJsonRuleConfigLight()
{
    json j{   
        {"name_rule" , "lighting rules"},
        {"type" , "Light"},
        {"id_" , "3"},
        {"name_" , "light_kitchen"},
        {"room_" , "kitchen"},
        {"id_sensor" , "10002"},
        {"id_actuator" , "45006"},
        {"minLux_" , 150.0},
        {"maxLux_" , 500.0},
        {"night_" , {
                        {"fromHour" , 21},
                        {"toHour" , 7},
                        {"fixedPosition" , -1}
                }},
        {"day_" , {
                        {"fromHour" , 7},
                        {"toHour" , 21},
                        {"fixedPosition" , -1}
                }},
        {"targetIlluminance_" , 300.0},
        {"confirmTicks_" , 3},
        {"fromHour" , 7},
        {"toHour" , 9},
        {"fixedPosition" , 10},
        {"enable_" , true}
    };

    return j;
}

TEST(RuleControlLightTest, Init)
{
    scada_core_testing_utils::FakeSensorState sensor(250.0);
    scada_core_testing_utils::FakeActuator actuator;
    RuleConfigLight cfg;
    
    ASSERT_NO_THROW(cfg.fromJson(makeJsonRuleConfigLight()));

    RuleControlLight control(sensor, actuator, cfg);

    EXPECT_FALSE(actuator.getState());

    EXPECT_EQ(sensor.lastValue(), 250.0);
}

TEST(CurtainPositionIntegrationTest, ShouldMoveToTargetPositionAt100Lux)
{
    scada_core_testing_utils::FakeSensorState sensor(100);
    scada_core_testing_utils::FakeActuatorPosition actuator;

    RuleConfigLight cfg;

    ASSERT_NO_THROW(cfg.fromJson(makeJsonRuleConfigLight()));

    RuleControlLight control(sensor, actuator, cfg);

    control.evaluate();

    EXPECT_EQ(actuator.getPosition(), 10);

    sensor.setLastValue(150);

    control.evaluate();

    EXPECT_EQ(actuator.getPosition(), 20);

    sensor.setLastValue(200);

    control.evaluate();

    EXPECT_EQ(actuator.getPosition(), 30);

    sensor.setLastValue(300);

    control.evaluate();

    EXPECT_EQ(actuator.getPosition(), 30); 
}

TEST(CurtainPositionIntegrationTest, ShouldCloseCurtainWhileLuxRemainsAboveTarget)
{
    int lux = 500;
    int start_position = 100;
    scada_core_testing_utils::FakeSensorState sensor(lux);
    scada_core_testing_utils::FakeActuatorPosition actuator;

    RuleConfigLight cfg;

    ASSERT_NO_THROW(cfg.fromJson(makeJsonRuleConfigLight()));

    RuleControlLight control(sensor, actuator, cfg, start_position);

    control.evaluate();

    EXPECT_EQ(actuator.getPosition(), start_position - 10);

    sensor.setLastValue(400);

    control.evaluate();

    EXPECT_EQ(actuator.getPosition(), start_position - 20);
}


