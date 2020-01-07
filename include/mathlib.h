//
// Created by tia on 2020/01/02.
//

#ifndef TIEOS_MATHLIB_H
#define TIEOS_MATHLIB_H

#include <cstdint>

namespace tiestd {

    typedef struct DIVMOD {
        int64_t div;
        int64_t mod;
    } DIVMOD;

    DIVMOD divmod(int64_t x, int64_t y);

}

#endif //TIEOS_MATHLIB_H
