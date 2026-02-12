#include <stdexcept>
#include "SmoothRandomSource.hpp"

SmoothRandomSource::SmoothRandomSource(double startValue,
                                        double deltaValue, 
                                        double minValue, 
                                        double maxValue)
        :   current_(startValue),   
            delta_(deltaValue),
            min_(minValue),
            max_(maxValue),
            gen_(std::random_device{}()),
            dist_(-deltaValue, deltaValue) 

{
    if(min_ > max_) {
        throw std::logic_error(
            "SmoothRandomSource: minValue > maxValue"
        );
    }

    if(current_ < min_ || current_ > max_){
        throw std::logic_error(
            "SmoothRandomSource: startValue out of range"
        );
    }

    if (delta_ <= 0) {   
        throw std::logic_error(
            "SmoothRandomSource: deltaValue must be > 0"
        );
    }
}

double SmoothRandomSource::readValue()
{
    double delta = dist_(gen_);
    current_ += delta;
    if(current_ < min_) current_ = min_;
    if(current_ > max_) current_ = max_;

    return current_;  
}
