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
#include "port/rtc.h"


namespace interrupt {
    extern tiestd::RingBuffer key_buffer;
    extern rtc::DateTimePack rtc_datetime;
    extern uint64_t timer_count;

    void int_default();
    void zero_div();
    void keyboard();
    void rtc();
    void timer();
}

#endif //TIEOS_INTERRUPT_H
