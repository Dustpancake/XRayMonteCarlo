//
// Created by ktulhu on 17/11/2018.
//

#include "xorshift.h"

uint64_t prng::s[2] = {42};

uint64_t prng::xorshift128plus() {
    uint64_t x = s[0];
    uint64_t const y = s[1];
    s[0] = y;
    x ^= x << 23; // a
    s[1] = x ^ y ^ (x >> 17) ^ (y >> 26); // b, c
    return s[1] + y;
}
