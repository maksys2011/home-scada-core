#pragma once
#include <vector>
#include <memory>

class Rule;

class RuleEngine
{
public:
    
    void addRule(std::unique_ptr<Rule> rules);
    void evaluate();

private:
    
    std::vector<std::unique_ptr<Rule>> rules_;

};