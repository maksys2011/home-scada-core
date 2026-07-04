#pragma once

#include "TelemetrySnapshot.hpp"
#include "ITelemetrySubscriber.hpp"

class QtGuiSubscriber : public ITelemetrySubscriber
{
private:
    TelemetrySnapshot snapshot_;
public:
    QtGuiSubscriber() = default;
    void onTelemetry(const TelemetrySnapshot& snapshot) override;
    const TelemetrySnapshot& getSnapshot() { return snapshot_; };
};


