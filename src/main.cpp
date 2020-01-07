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



using namespace tiestd;

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

    segment::GDT = segment::SegmentDescriptorTable((void*)0x0);
    segment::GDT.push(0);
    segment::GDT.push_code64(0, 1, 1, 1, 0, 1, 1, 0);
    segment::GDT.push_data(0, 0xffffff, 0, 1, 1, 1, 1, 1, 0);
    segment::GDT.load_global_descriptor_table();
    segment::GDT.set_segment(8, 16, 16);


    segment::IDT = segment::InterruptDescriptorTable((void*)0x2000);
    for (uint64_t i = 0; i < 256; i ++) {
        segment::IDT.push((uint64_t)interrupt::int_default, 8, 0xe, 1, 0, 0);
    }
    segment::IDT.set(0, (uint64_t)interrupt::zero_div, 8, 0xe, 1, 0, 0);
    segment::IDT.set(0x21, (uint64_t)interrupt::keyboard, 8, 0xe, 1, 0, 0);
    segment::IDT.set(0x28, (uint64_t)interrupt::rtc, 8, 0xe, 1, 0, 0);
    segment::IDT.load_interrupt_descriptor_table();

    assembly::init_rtc();
    assembly::init_pic();
    assembly::set_pic(0b1111'1001, 0b1111'1110);

    __asm__ volatile ("sti");

//    i = 10 / 0;

    while (1) {
        __asm__ volatile ("hlt");
    }
}

}