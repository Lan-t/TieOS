//
// Created by tia on 2020/01/06.
//



#include <cstdint>

#include "main.h"
#include "stringlib.h"
#include "GraphicsConfig.h"
#include "bufferlib.h"
#include "port/rtc.h"


namespace interrupt {
    tiestd::RingBuffer key_buffer;

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
        __asm__ volatile (
        "leave \n"
        "iretq"
        );
    }

    void rtc() {
        rtc::DateTimePack date_time = rtc::get_time();

        __asm__ volatile (
        "mov al, 0x0c \n"
        "out 0x70, al \n"
        "in al, 0x71 \n"
        "mov al, 0x20 \n"
        "out 0xa0, al \n"
        "out 0x20, al"
        );

        char buf[9];
        tiestd::itoa(date_time.horh, buf, 1, 10, tiestd::FILL_SPACE);
        tiestd::itoa(date_time.horl, buf + 1, 1, 10, tiestd::FILL_SPACE | tiestd::ZERO_IS_EMPTY);
        buf[2] = ':';
        tiestd::itoa(date_time.minh, buf + 3, 1, 10, tiestd::FILL_SPACE);
        tiestd::itoa(date_time.minl, buf + 4, 1, 10, tiestd::FILL_SPACE | tiestd::ZERO_IS_EMPTY);
        buf[5] = ':';
        tiestd::itoa(date_time.sech, buf + 6, 1, 10, tiestd::FILL_SPACE);
        tiestd::itoa(date_time.secl, buf + 7, 1, 10, tiestd::FILL_SPACE | tiestd::ZERO_IS_EMPTY);
        buf[8] = 0;
        gGraphicsConfig.put_string(buf, gGraphicsConfig.get_console_width() - 8, 0, 0x0f0f0f, 0xffffff);

        __asm__ volatile (
        "leave \n"
        "iretq"
        );
    }
}
