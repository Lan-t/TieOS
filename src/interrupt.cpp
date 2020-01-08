//
// Created by tia on 2020/01/06.
//



#include <cstdint>

#include "main.h"
#include "stringlib.h"
#include "GraphicsConfig.h"
#include "bufferlib.h"
#include "port/rtc.h"

#define interrupt_return __asm__ volatile (\
"leave \n" \
"iretq" \
)


namespace interrupt {
    tiestd::RingBuffer key_buffer;
    rtc::DateTimePack rtc_datetime;
    uint64_t timer_count = 0;

    void stop() {
        while (1) {
            __asm__ volatile ("hlt");
        }
    }

    void int_default() {
        gGraphicsConfig.put_string("DEFAULT", 0, 0, 0xff0000, 0x000000);
        stop();
    }

    void zero_div() {
        gGraphicsConfig.put_string("ZERO DIV", 0, 0, 0xff0000, 0x000000);
        stop();
    }

    void keyboard() {
        uint8_t key;
        __asm__ volatile ("in al, 0x60" : "=a"(key));
        key_buffer.write(key);
        key_buffer.put(1, 45, 0xffff00);
        key_buffer.read();
        __asm__ volatile (
        "mov al, 0x20 \n"
        "out 0x20, al"
        );

        interrupt_return;
    }

    void rtc() {
        rtc::DateTimePack date_time = rtc::get_datetime();
        rtc_datetime = date_time;

        __asm__ volatile (
        "mov al, 0x0c \n"
        "out 0x70, al \n"
        "in al, 0x71 \n"
        "mov al, 0x20 \n"
        "out 0xa0, al \n"
        "out 0x20, al"
        );

        interrupt_return;
    }

    void timer() {
        timer_count++;

        __asm__ volatile (
        "mov al, 0x20 \n"
        "out 0x20, al"
        );

        interrupt_return;
    }
}
