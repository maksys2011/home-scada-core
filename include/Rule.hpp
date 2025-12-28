#pragma once

class Rule
{
public:
    virtual ~Rule() = default;
    virtual void evaluate() = 0;
};