#include <gtest/gtest.h>
#include <optional>
#include "RuleThermostat.hpp"
#include "RuleThermostatConfig.hpp"
#include "ISensorState.hpp"
#include "IActuator.hpp"
#include "ITransport.hpp"
#include "Enum.hpp"
#include "scada_core_testing_utils.hpp"

static json makeJsonRuleThermostat()
{
    json j{
        {"name_rule" , "temperature rules"},
        {"type" , "Thermostat"},
        {"rule_id" , "1"}, 
        {"sensor_name", "temperature_kitchen"},
        {"sensor_id" , "10001"},
        {"actuator_name" , "split_system"},
        {"actuator_id" , "35001"},
        {"minTemp" , 21.0},
        {"maxTemp" , 22.0}
    }; 
    return j;
}

TEST(RuleThermostatTest, Init)
{
    scada_core_testing_utils::FakeSensorState sensor(20.2);
    scada_core_testing_utils::FakeActuator actuator;
    RuleThermostatConfig cfg;
    
    EXPECT_NO_THROW(cfg.fromJson(makeJsonRuleThermostat()));
    EXPECT_NO_THROW(RuleThermostat(sensor, actuator, cfg));
}

TEST(RuleThermostatIntegrationTest,  TurnOnCommandActuator)
{
    scada_core_testing_utils::FakeSensorState sensor(15.0);
    scada_core_testing_utils::FakeActuator actuator;
    RuleThermostatConfig cfg;

    EXPECT_NO_THROW(cfg.fromJson(makeJsonRuleThermostat()));

    RuleThermostat rule(sensor, actuator, cfg);

    EXPECT_FALSE(actuator.getState());

    rule.evaluate();

    EXPECT_TRUE(actuator.getState());
}

TEST(RuleThermostatIntegrationTest,  TurnOffCommandActuator)
{
    scada_core_testing_utils::FakeSensorState sensor(25.0);
    scada_core_testing_utils::FakeActuator actuator;
    RuleThermostatConfig cfg;

    EXPECT_NO_THROW(cfg.fromJson(makeJsonRuleThermostat()));

    RuleThermostat rule(sensor, actuator, cfg);

    EXPECT_FALSE(actuator.getState());

    rule.evaluate();

    EXPECT_FALSE(actuator.getState());
}

TEST(RuleThermostatIntegrationTest,  EmptySensorValueDoesNotChangeActuator)
{
    std::optional<double> val;
    scada_core_testing_utils::FakeSensorState sensor(val);
    scada_core_testing_utils::FakeActuator actuator;
    RuleThermostatConfig cfg;

    EXPECT_NO_THROW(cfg.fromJson(makeJsonRuleThermostat()));

    RuleThermostat rule(sensor, actuator, cfg);

    EXPECT_FALSE(actuator.getState());

    rule.evaluate();

    EXPECT_FALSE(actuator.getState());
}

TEST(RuleThermostatIntegrationTest, TargetTemperature_LowerBound)
{
    scada_core_testing_utils::FakeSensorState sensor(21.0);
    scada_core_testing_utils::FakeActuator actuator;
    RuleThermostatConfig cfg;

    EXPECT_NO_THROW(cfg.fromJson(makeJsonRuleThermostat()));

    RuleThermostat rule(sensor, actuator, cfg);

    EXPECT_FALSE(actuator.getState());

    rule.evaluate();

    EXPECT_FALSE(actuator.getState());

}

TEST(RuleThermostatIntegrationTest, WhenTempEqualsMin_ActuatorShouldStayOff)
{
    scada_core_testing_utils::FakeSensorState sensor(21.0);
    scada_core_testing_utils::FakeActuator actuator;
    RuleThermostatConfig cfg;

    EXPECT_NO_THROW(cfg.fromJson(makeJsonRuleThermostat()));

    RuleThermostat rule(sensor, actuator, cfg);

    EXPECT_FALSE(actuator.getState());

    rule.evaluate();

    EXPECT_FALSE(actuator.getState());

}

TEST(RuleThermostatIntegrationTest, AtMinTemperature_ActuatorIsInactive)
{
    scada_core_testing_utils::FakeSensorState sensor(22.0);
    scada_core_testing_utils::FakeActuator actuator;
    RuleThermostatConfig cfg;

    EXPECT_NO_THROW(cfg.fromJson(makeJsonRuleThermostat()));

    RuleThermostat rule(sensor, actuator, cfg);

    EXPECT_FALSE(actuator.getState());

    rule.evaluate();

    EXPECT_FALSE(actuator.getState());
}