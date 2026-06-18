#include <gtest/gtest.h>
#include <optional>
#include "RuleThermostat.hpp"
#include "RuleThermostatConfig.hpp"
#include "ISensorState.hpp"
#include "IActuator.hpp"
#include "ITransport.hpp"
#include "Enum.hpp"

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

class FakeSensorState : public ISensorState
{
public:
    FakeSensorState(std::optional<double> val)
    {
        lastValue_ = val;
    }

    std::optional<double> lastValue() const override { return lastValue_; };

private:

    std::optional<double> lastValue_;
};

class FakeActuator : public IActuator
{
public:

    const std::string& getId() const override{ return id_; };
    bool execute(CommandType cmd, const CommandValue& val) override { return true; };
    virtual CommandType getCmd() const override { return typeCmd_; };
    bool getState() const override { return state_; };
	void setState(bool state) override { state_ = state;};
    void setTypeCmd(CommandType typeCmd) { typeCmd_ = typeCmd; };
	void print() const override {};


private:
    std::string id_;
    CommandType typeCmd_ = CommandType::Unknown;
    bool state_ = false;

};

TEST(RuleThermostatTest, Init)
{
    FakeSensorState sensor(20.2);
    FakeActuator actuator;
    RuleThermostatConfig cfg;
    EXPECT_NO_THROW(cfg.fromJson(makeJsonRuleThermostat()));
    EXPECT_NO_THROW(RuleThermostat(sensor, actuator, cfg));
}

TEST(RuleThermostatIntegrationTest,  TurnOnCommandActuator)
{
    FakeSensorState sensor(15.0);
    FakeActuator actuator;
    RuleThermostatConfig cfg;

    EXPECT_NO_THROW(cfg.fromJson(makeJsonRuleThermostat()));

    RuleThermostat rule(sensor, actuator, cfg);

    EXPECT_FALSE(actuator.getState());

    rule.evaluate();

    EXPECT_TRUE(actuator.getState());
}

TEST(RuleThermostatIntegrationTest,  TurnOffCommandActuator)
{
    FakeSensorState sensor(25.0);
    FakeActuator actuator;
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
    FakeSensorState sensor(val);
    FakeActuator actuator;
    RuleThermostatConfig cfg;

    EXPECT_NO_THROW(cfg.fromJson(makeJsonRuleThermostat()));

    RuleThermostat rule(sensor, actuator, cfg);

    EXPECT_FALSE(actuator.getState());

    rule.evaluate();

    EXPECT_FALSE(actuator.getState());
}