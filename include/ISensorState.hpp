#pragma once 

#include <optional>

#include "TelemetrySnapshot.hpp"

class ISensorState
{
public:

    virtual ~ISensorState() = default;

    virtual std::optional<double> lastValue() const = 0;
    virtual TelemetrySnapshot getSnapShot() const = 0;

};