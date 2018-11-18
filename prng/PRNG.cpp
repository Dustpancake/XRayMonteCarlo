//
// Created by ktulhu on 17/11/2018.
//

#include <PRNG.h>
#include <limits>

uint64_t prng::s[2] = {42};

uint64_t prng::xorshift128plus() {
    uint64_t x = s[0];
    uint64_t const y = s[1];
    s[0] = y;
    x ^= x << 23; // a
    s[1] = x ^ y ^ (x >> 17) ^ (y >> 26); // b, c
    return s[1] + y;
}

template<typename T>
T rand(T lower, T upper) {
    T retval;
    uint64_t v1 = prng::xorshift128plus();
    uint64_t v2 = std::numeric_limits<uint64_t>::max();
    long double frac =  v1 / static_cast<long double>(v2);
    retval = static_cast<T>((upper - lower) * frac + lower);
    return retval;

}

float prng::rfloat(float lower, float upper) {
    return rand<float>(lower, upper);
}

double prng::rdouble(double lower, double upper) {
    return rand<double>(lower, upper);
}

long double prng::rldouble(long double lower, long double upper) {
    return rand<long double>(lower, upper);
}
