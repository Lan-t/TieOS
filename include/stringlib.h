//
// Created by tia on 2020/01/02.
//

#ifndef TIEOS_STRINGLIB_H
#define TIEOS_STRINGLIB_H

#include <cstdint>

namespace tie_os_std {

    enum ITOA_FRAGS {
        DEFAULT             = 0,
        FILL_SPACE          = 0x1,
        FILL_ZERO           = 0x2,
        IS_SIGNED           = 0x4,
        SET_SIGN            = 0x8,
        UPPERCASE           = 0x10,
        SET_NULL_TERMINATE  = 0x20,
    };

    void itoa(uint64_t value, char *buffer, uint64_t buffer_size, uint64_t radix, uint32_t flags);

}

#endif //TIEOS_STRINGLIB_H
