//
// Created by tia on 2020/01/06.
//

#ifndef TIEOS_INTERRUPT_H
#define TIEOS_INTERRUPT_H

#include <cstdint>

#include "main.h"
#include "stringlib.h"
#include "GraphicsConfig.h"
#include "bufferlib.h"


namespace interrupt {
    extern tie_os_std::RingBuffer key_buffer;

    void stop();

    void int_default();
    void zero_div();
    void keyboard();

}

#endif //TIEOS_INTERRUPT_H
