#pragma once

#include "TelemetrySnapshot.hpp"

class ITelemetrySubscriber
{
public:
    virtual ~ITelemetrySubscriber() = default;
    virtual void onTelemetry(const TelemetrySnapshot& snapshot) = 0;
};

