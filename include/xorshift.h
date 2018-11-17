//
// Created by ktulhu on 17/11/2018.
//

#ifndef XRAYMONTECARLO_XORSHIFT_H
#define XRAYMONTECARLO_XORSHIFT_H

#include <cstdint>

namespace prng {
    extern uint64_t s[2];
    uint64_t xorshift128plus();
}

#endif //XRAYMONTECARLO_XORSHIFT_H
