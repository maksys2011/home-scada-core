#pragma once

#include <vector>

#include "ITelemetrySubscriber.hpp"
#include "TelemetrySnapshot.hpp"

class Dispatcher
{
private:
    std::vector<ITelemetrySubscriber*> subscribers; 
    void notifySubscribers(const TelemetrySnapshot& snapshot);
public:
    void publishetValid(const TelemetrySnapshot& snapshot);
    void addSubscriber(ITelemetrySubscriber* subsciber);
};
