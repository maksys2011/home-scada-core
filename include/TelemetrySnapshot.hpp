#pragma once

#include <chrono>
#include <string>
#include <optional>
#include "Enum.hpp"

struct TelemetrySnapshot
{
    ValidData valid = ValidData::NO;
    std::string id{};
    std::optional<double> lastValue;
    State currentState = State::INVALID;
    std::chrono::system_clock::time_point timestamp;
};
