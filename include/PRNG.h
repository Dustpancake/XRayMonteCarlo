//
// Created by ktulhu on 17/11/2018.
//

#ifndef XRAYMONTECARLO_XORSHIFT_H
#define XRAYMONTECARLO_XORSHIFT_H

#include <cstdint>
#include <functional>

namespace prng {
    extern uint64_t s[2];
    uint64_t xorshift128plus();

    float rfloat(float lower, float upper);
    double rdouble(double lower, double upper);
    long double rldouble(long double lower, long double upper);

    // generate n floats with callback on each
    void ncallback(int n, double lower, double upper, const std::function<void (double)>& callback);
};

#endif //XRAYMONTECARLO_XORSHIFT_H
