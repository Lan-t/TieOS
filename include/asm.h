//
// Created by tia on 2020/01/06.
//

#ifndef TIEOS_ASM_H
#define TIEOS_ASM_H

#include <cstdint>

namespace assembly {
    void init_pic();
    void set_pic(uint8_t master, uint8_t slave);
}

#endif //TIEOS_ASM_H
