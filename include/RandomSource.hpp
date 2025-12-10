#pragma once
#include <Source.hpp>
#include <random>

class RandomSource : public Source {
public:
    RandomSource(double minValue, double maxValue);
    double readValue() override;
private:
    double min_;
    double max_;
    std::mt19937 gen_;
    std::uniform_real_distribution<double> dist_;
};

