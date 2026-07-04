#include "QtGuiSubscriber.hpp"

void QtGuiSubscriber::onTelemetry(const TelemetrySnapshot &snapshot)
{
    if(snapshot.valid == ValidData::YES){
        snapshot_ = snapshot;
    }  
}