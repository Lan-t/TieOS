//
// Created by tia on 2020/01/06.
//

#ifndef TIEOS_INTERRUPT_H
#define TIEOS_INTERRUPT_H

#include <cstdint>

#include "main.h"
#include "stringlib.h"
#include "GraphicsConfig.h"


namespace interrupt {
    void stop();

    void int_default();
    void zero_div();
}

#endif //TIEOS_INTERRUPT_H
