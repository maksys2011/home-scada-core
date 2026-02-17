#pragma once

class Source 
{
public:
    virtual ~Source() = default;
    virtual double readValue() = 0;
    virtual bool connect() = 0;
};