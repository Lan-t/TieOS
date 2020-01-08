//
// Created by tia on 2020/01/06.
//

#include <cstdint>

#define outp(port, value) __asm__ volatile ( \
    "mov al, " #value "\n"\
    "out " #port ", al" \
)

#define outp_m(port, value) __asm__ volatile ( \
    "mov al, %0 \n"\
    "out "#port", al" \
    : : "r"(value) \
)


namespace assembly {
    void init_pic() {
        outp(0x20, 0x11);
        outp(0x21, 0x20);
        outp(0x21, 0x04);
        outp(0x21, 0x05);
        outp(0x21, 0xff);

        outp(0xa0, 0x11);
        outp(0xa1, 0x28);
        outp(0xa1, 0x02);
        outp(0xa1, 0x01);
        outp(0xa1, 0xff);
    }

    void set_pic(uint8_t master, uint8_t slave) {
        outp_m(0x21, master);
        outp_m(0xa1, slave);
    }

    void init_rtc() {
        outp(0x70, 0x0b);
        __asm__ volatile (
                "in al, 0x71 \n"
                "or al, 0x10 \n"
                "out 0x71, al"
                );
    }

    void init_timer() {
        outp(0x43, 0b00110100);
        outp(0x40, 0x9c);
        outp(0x40, 0x2e);
    }
}
