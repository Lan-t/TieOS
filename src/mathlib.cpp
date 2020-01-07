//
// Created by tia on 2020/01/02.
//

#include <cstdint>
#include "mathlib.h"

namespace tiestd {

    DIVMOD divmod(int64_t x, int64_t y) {
        DIVMOD ans;
        __asm__ volatile (
        "div rcx"
        : "=a"(ans.div), "=d"(ans.mod)
        : "a"(x), "d"(0), "c"(y)
        );
        return ans;
    }
}
