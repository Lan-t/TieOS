#include <cstdint>

#include "main.h"
#include "GraphicsConfig.h"
#include "MemoryMap.h"
#include "stringlib.h"
#include "cpu/SegmentDescriptorTable.h"
#include "interrupt.h"
#include "cpu/InterruptDescriptorTable.h"
#include "asm.h"



graphics_config::GraphicsConfig gGraphicsConfig;
memory_map::MemoryMap gMemoryMap;



using namespace tie_os_std;

int64_t f(int64_t x) {
    return x * x * x / 25;
}


extern "C" {

void _start(graphics_config::_GraphicsConfig *graphicsConfig, memory_map::_MemoryMap *memoryMap) {
    gGraphicsConfig = graphics_config::GraphicsConfig(graphicsConfig);
    gMemoryMap = memory_map::MemoryMap(memoryMap);

    uint64_t i;
    char buf[100];


    gGraphicsConfig.fill_screen(0x112233);

    gMemoryMap.put_memory_info(gGraphicsConfig);


    __asm__ volatile ("cli");

    auto GDT = cpu::SegmentDescriptorTable((void*)0x1000);
    GDT.push(0);
    GDT.push_code64(0, 1, 1, 1, 0, 1, 1, 0);
    GDT.push_data(0, 0xffffff, 0, 1, 1, 1, 1, 1, 0);

    GDT.load_global_descriptor_table();

    GDT.set_segment(8, 16, 16);

    cpu::DTR gdtr;
    asm(
            "lea rax, %0 \n"
            "sgdt [rax]"
            : : "m"(gdtr)
            );

    i = 32;

    for (auto *a = (uint64_t*)gdtr.base; (uint64_t)a <= gdtr.base + gdtr.limit; a ++) {
        itoa(*a, buf, 17, 16, SET_NULL_TERMINATE | FILL_ZERO);
        gGraphicsConfig.put_string(buf, 20, i ++, 0xffffffff);
    }




    auto IDT = cpu::InterruptDescriptorTable((void*)0x2000);

    for (uint64_t i = 0; i < 256; i ++) {
        IDT.push((uint64_t)interrupt::int_default, 8, 0xe, 1, 0, 0);
    }

    IDT.set(0, (uint64_t)interrupt::zero_div, 8, 0xe, 1, 0, 0);
    IDT.set(0x21, (uint64_t)interrupt::keyboard, 8, 0xe, 1, 0, 0);

    IDT.load_interrupt_descriptor_table();

    assembly::init_pic();
    assembly::set_pic(0b1111'1101, 0b1111'1111);

    __asm__ volatile ("sti");

//    i = 10 / 0;

    while (1) {
        __asm__ volatile ("hlt");
    }
}

}