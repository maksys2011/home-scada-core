#include  <RandomSource.hpp>

RandomSource::RandomSource(double minValue, double maxValue)
    : min_(minValue),
        max_(maxValue),
        gen_(std::random_device{}()),
        dist_(minValue, maxValue)
{}
double RandomSource::readValue()
{
    return dist_(gen_);
}
