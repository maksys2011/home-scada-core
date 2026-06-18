#pragma once 
#include <optional>

class ISensorState
{
public:

    virtual ~ISensorState() = default;

    virtual std::optional<double> lastValue() const = 0;
};