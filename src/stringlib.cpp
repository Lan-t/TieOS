//
// Created by tia on 2020/01/02.
//

#include <cstdint>
#include "stringlib.h"
#include "mathlib.h"

namespace tie_os_std {

    static const char NUMBER[] = "0123456789abcdefghijklmnopqrstuvwxyz";
    static const char NUMBER_UPPERCASE[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    void itoa(uint64_t value, char *buffer, uint64_t buffer_size, uint64_t radix, uint32_t flags) {
        uint8_t is_minas = 0;

        if (flags & IS_SIGNED) {
            if ((int64_t) value < 0) {
                value = (int64_t) value * -1;
                is_minas = 1;
            }
        }

        if (flags & SET_SIGN || is_minas) {
            char sign = is_minas ? '-' : '+';
            *(buffer++) = sign;
            buffer_size--;
        }

        if (flags & SET_NULL_TERMINATE) {
            buffer_size--;
        }

        char const *charset;
        if (flags & UPPERCASE) {
            charset = NUMBER_UPPERCASE;
        } else {
            charset = NUMBER;
        }

        char tmp_buff[buffer_size];
        uint64_t i = buffer_size;
        uint64_t remain = value;

        while (remain && i) {
            DIVMOD dm = divmod(remain, radix);
            remain = dm.div;
            tmp_buff[--i] = charset[dm.mod];
        }

        uint64_t j;
        if (!(flags & (FILL_SPACE | FILL_ZERO))) {
            for (j = 0; j < buffer_size - i; j++) {
                buffer[j] = tmp_buff[i + j];
            }
        } else {
            char fill;
            if (flags & FILL_ZERO) {
                fill = '0';
            } else if (flags & FILL_SPACE) {
                fill = ' ';
            }

            for (j = 0; j < i; j++) {
                buffer[j] = fill;
            }
            for (; j < buffer_size; j++) {
                buffer[j] = tmp_buff[j];
            }
        }
        if (flags & SET_NULL_TERMINATE) {
            buffer[j] = 0;
        }
    }

}
