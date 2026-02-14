#pragma once

class Source 
{
public:
    virtual ~Source() = default;
    virtual double readValue() = 0;
    // virtual void connect() = 0;
};