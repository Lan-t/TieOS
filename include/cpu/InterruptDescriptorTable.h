//
// Created by tia on 2020/01/06.
//

#ifndef TIEOS_INTERRUPTDESCRIPTORTABLE_H
#define TIEOS_INTERRUPTDESCRIPTORTABLE_H

#include <cstdint>

#include "main.h"
#include "SegmentDescriptorTable.h"

namespace segment {
    class InterruptDescriptor {
    private:
        uint16_t m_offset_00_15;
        uint16_t m_segment_selector;
        unsigned m_ist      : 3;
        unsigned m__zero1   : 5;
        unsigned m_type     : 4;
        unsigned m__zero2   : 1;
        unsigned m_dpl      : 2;
        unsigned m_p        : 1;
        uint16_t m_offset_31_16;
        uint32_t m_offset_63_32;
        uint32_t m__reserved;

    public:

        void
        set(uint64_t offset, uint16_t segment_selector, uint8_t type, uint8_t Present, uint8_t DescriptorPrivilegeLevel,
            uint8_t IST) {
            m__zero1 = 0;
            m__zero2 = 0;
            m__reserved = 0;
            m_dpl = 0;
            m_p = 0;

            if (Present) m_p = 1;
            if (DescriptorPrivilegeLevel) m_dpl = 3;

            m_type = type;
            m_ist = IST;
            m_offset_00_15 = offset;
            m_offset_31_16 = offset >> 16u;
            m_offset_63_32 = offset >> 32u;
            m_segment_selector = segment_selector;
        }
    };

    class InterruptDescriptorTable {
    private:
        InterruptDescriptor *interrupt_descriptor_table;
        uint64_t length = 0;

    public:
        InterruptDescriptorTable() {
            interrupt_descriptor_table = (InterruptDescriptor*)0;
        }

        InterruptDescriptorTable(void *offset) {
            interrupt_descriptor_table = (InterruptDescriptor *) offset;
        }

        __attribute__((always_inline)) inline void load_interrupt_descriptor_table() {
            DTR idtr = {(uint16_t) (sizeof(InterruptDescriptor) * length - 1), (uint64_t) interrupt_descriptor_table};

            __asm__ volatile (
            "lea rax, %0 \n"
            "lidt [rax]"
            : : "m"(idtr));
        }

        void push(uint64_t offset, uint16_t segment_selector, uint8_t type, uint8_t Present,
                  uint8_t DescriptorPrivilegeLevel,
                  uint8_t IST) {
            interrupt_descriptor_table[length++].set(offset, segment_selector, type, Present, DescriptorPrivilegeLevel,
                                                     IST);
        }

        void set(uint64_t index, uint64_t offset, uint16_t segment_selector, uint8_t type, uint8_t Present,
                  uint8_t DescriptorPrivilegeLevel,
                  uint8_t IST) {
            interrupt_descriptor_table[index].set(offset, segment_selector, type, Present, DescriptorPrivilegeLevel,
                                                     IST);
        }
    };

    extern InterruptDescriptorTable IDT;
}

#endif //TIEOS_INTERRUPTDESCRIPTORTABLE_H
