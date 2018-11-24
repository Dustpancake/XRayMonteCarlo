//
// Created by ktulhu on 17/11/2018.
//

#include <PRNG.h>
#include <limits>

uint64_t prng::s[2] = {448232, 99};

uint64_t prng::xorshift128plus() {
    uint64_t a = s[0], b = s[1];
    s[0] = b;
    a ^= a << 23;
    a ^= a >> 17;
    a ^= b;
    a ^= b >> 26;
    s[1] = a;
    return a + b;
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

void prng::ncallback(int n, double lower, double upper, const std::function<void(double)> &callback) {
    for (int i = 0; i<n; i++) {
        double r = prng::rdouble(lower, upper);
        callback(r);
    }
}
