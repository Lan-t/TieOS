//
// Created by tia on 2020/01/06.
//


#include <cstdint>

#include "main.h"
#include "bufferlib.h"


namespace tiestd {
    uint8_t buf[3 * BUFFER_LENGTH] = {0};


    int RingBuffer::write(uint8_t value) {
        if ((wp + 1) % BUFFER_LENGTH == rp) {
            return 1;
        }
        buffer[wp] = value;
        wp = (wp + 1) % BUFFER_LENGTH;
        return 0;
    }

    uint8_t RingBuffer::read() {
        if (rp == wp) {
            return 0;
        }
        uint8_t v = buffer[rp];
        rp = (rp + 1) % BUFFER_LENGTH;
        return v;
    }

    void RingBuffer::put(uint64_t x, uint64_t y, uint32_t color) {
        for (uint64_t i = 0, p = rp; i < BUFFER_LENGTH; i ++, p --) {
            itoa(buffer[p], (char*)(buf + i * 3), 2, 16, FILL_ZERO);
            buf[i * 3 + 2] = ' ';
            if (!p) p = BUFFER_LENGTH;
        }
        buf[BUFFER_LENGTH * 3 - 1] = 0;
        gGraphicsConfig.put_string((char*)buf, x, y, color, 0x112233);
    }
}

