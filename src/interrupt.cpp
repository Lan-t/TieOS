//
// Created by tia on 2020/01/06.
//



#include <cstdint>

#include "main.h"
#include "stringlib.h"
#include "GraphicsConfig.h"


namespace interrupt {
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
}
