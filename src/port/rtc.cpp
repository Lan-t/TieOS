//
// Created by tia on 2020/01/07.
//


#include <cstdint>

#include "port/rtc.h"

namespace rtc {
    DateTimePack get_time() {
        uint64_t date_time = 0xffffffffffffffff;

        __asm__ volatile (
        "mov al, 0x00 \n"
        "out 0x70, al \n"
        "in al, 0x71 \n"
        "shl rax, 8 \n"

        "mov al, 0x02 \n"
        "out 0x70, al \n"
        "in al, 0x71 \n"
        "shl rax, 8 \n"

        "mov al, 0x04 \n"
        "out 0x70, al \n"
        "in al, 0x71 \n"
        "shl rax, 24"

        : "=a"(date_time)
        );

        return *(DateTimePack*)&date_time;
    }

    DateTimePack get_datetime() {
        DateTimePack datetime;

        __asm__ volatile (
        "mov al, 0x00 \n"
        "out 0x70, al \n"
        "in al, 0x71 \n"
        "shl rax, 8 \n"

        "mov al, 0x02 \n"
        "out 0x70, al \n"
        "in al, 0x71 \n"
        "shl rax, 8 \n"

        "mov al, 0x04 \n"
        "out 0x70, al \n"
        "in al, 0x71 \n"
        "shl rax, 8 \n"

        "mov al, 0x07 \n"
        "out 0x70, al \n"
        "in al, 0x71 \n"
        "shl rax, 8 \n"

        "mov al, 0x08 \n"
        "out 0x70, al \n"
        "in al, 0x71 \n"
        "shl rax, 8 \n"

        "mov al, 0x09 \n"
        "out 0x70, al \n"
        "in al, 0x71 \n"

        : "=a"(datetime)
        );

        return datetime;
    }
}
