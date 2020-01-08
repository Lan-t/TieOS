//
// Created by tia on 2020/01/06.
//

#ifndef TIEOS_BUFFERLIB_H
#define TIEOS_BUFFERLIB_H

#include <cstdint>

#include "stringlib.h"
#include "main.h"

#define BUFFER_LENGTH 40

namespace tiestd {

    class RingBuffer {
    private:
        uint8_t buffer[BUFFER_LENGTH];
        uint64_t wp;
        uint64_t rp;

    public:
        RingBuffer() {
            wp = 0;
            rp = 0;
        }

        int write(uint8_t value);
        uint8_t read();
        void put(uint64_t x, uint64_t y, uint32_t color);
    };
}

#endif //TIEOS_BUFFERLIB_H
