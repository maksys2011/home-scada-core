#include "Dispatcher.hpp"

void Dispatcher::notifySubscribers(const TelemetrySnapshot &snapshot)
{
    for(auto& subscriber : subscribers){
        if(subscriber){
            subscriber->onTelemetry(snapshot);
        }
    }
}

void Dispatcher::publishetValid(const TelemetrySnapshot &snapshot)
{
    if(snapshot.valid == ValidData::YES){
        notifySubscribers(snapshot);    
    }
}

void Dispatcher::addSubscriber(ITelemetrySubscriber *subsciber)
{
    subscribers.push_back(subsciber);
}
