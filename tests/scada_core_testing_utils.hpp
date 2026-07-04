#pragma once
#include "IActuator.hpp"
#include "ISensorState.hpp"
#include "TelemetrySnapshot.hpp"
#include "ITelemetrySubscriber.hpp"

namespace scada_core_testing_utils
{
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
    int setPosition() { return position; };
private:
    std::string id_;
    CommandType typeCmd_ = CommandType::Unknown;
    bool state_ = false;
    int position = 0;

};

class FakeSensorState : public ISensorState
{
public:
    FakeSensorState(std::optional<double> val)
    {
        lastValue_ = val;
    }

    std::optional<double> lastValue() const override { return lastValue_; };

    TelemetrySnapshot getSnapShot() const override{ return snapshot_; };

    void setLastValue(double value){
        lastValue_ = value;
    }

private:
    TelemetrySnapshot snapshot_;
    std::optional<double> lastValue_;
};

class FakeActuatorPosition : public IActuator
{
public:
    const std::string& getId() const override{ return id_; };
    bool execute(CommandType cmd, const CommandValue& val) override {
        setPosition(std::get<int>(val));
        return true; 
    };
    virtual CommandType getCmd() const override { return typeCmd_; };
    bool getState() const override { return state_; };
	void setState(bool state) override { state_ = state;};
    void setTypeCmd(CommandType typeCmd) { typeCmd_ = typeCmd; };
	void print() const override {};
    void setPosition(int val) { 
        current_position = val; 
    };

    int getPosition() { return current_position; };

private:
    std::string id_{};
    CommandType typeCmd_ = CommandType::Unknown;
    bool state_ = false;
    int position = 0;
    int current_position = 0;

};

class FakeSubscriber : public ITelemetrySubscriber
{
private:
    TelemetrySnapshot snapshot_;
    bool call = false;
public:
    FakeSubscriber() = default;
    void onTelemetry(const TelemetrySnapshot& snapshot) override{
        if(snapshot.valid == ValidData::YES){
            snapshot_ = snapshot;
            call = true;
        }
    };
    const TelemetrySnapshot& getSnapshot() { return snapshot_; };
    bool getCall() { return call; };
    
};



}