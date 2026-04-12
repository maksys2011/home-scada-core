#include <iostream>
#include "RuleEngine.hpp"
#include "Rule.hpp"

void RuleEngine::addRule(std::unique_ptr<Rule> rules)
{
    rules_.push_back(std::move(rules));
}

void RuleEngine::evaluate()
{
    for (auto& rule : rules_)
    {
        rule->evaluate();
    }
}

size_t RuleEngine::getSize()
{
    return rules_.size();
}
