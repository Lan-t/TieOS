//
// Created by tia on 2020/01/04.
//

#ifndef TIEOS_SEGMENTDESCRIPTORTABLE_H
#define TIEOS_SEGMENTDESCRIPTORTABLE_H

#include <cstdint>

namespace cpu {

#pragma pack(1)

    struct DTR {
        uint16_t limit;
        uint64_t base;
    };

#pragma pack()


    class SegmentDescriptor {
    private:
        uint64_t _segment_descriptor;

    public:

        void set_data(uint32_t base, uint32_t limit, uint8_t ExpansionDirection, uint8_t Writeable, uint8_t Accessed,
                      uint8_t Granularity, uint8_t Big, uint8_t Present, uint8_t DescriptorPrivilegeLevel) {
            _segment_descriptor = 1ul << 44u;

            if (Granularity) _segment_descriptor |= 1ul << 55u;
            if (Big) _segment_descriptor |= 1ul << 54u;
            if (Present) _segment_descriptor |= 1ul << 47u;
            if (DescriptorPrivilegeLevel) _segment_descriptor |= 3ul << 45u;
            if (ExpansionDirection) _segment_descriptor |= 1ul << 42u;
            if (Writeable) _segment_descriptor |= 1ul << 41u;
            if (Accessed) _segment_descriptor |= 1ul << 40u;

            _segment_descriptor |= (uint64_t) (limit >> 16u) << 48u;
            _segment_descriptor |= (uint64_t) (0xffffu & limit);

            _segment_descriptor |= (uint64_t) (base >> 24u) << 56u;
            _segment_descriptor |= (uint64_t) (0xffffffu & base) << 16u;
        }

        void set_code(uint32_t base, uint32_t limit, uint8_t Conforming, uint8_t Readable, uint8_t Accessed,
                      uint8_t Granularity, uint8_t Default, uint8_t Present, uint8_t DescriptorPrivilegeLevel) {
            _segment_descriptor = 3ul << 43u;

            if (Granularity) _segment_descriptor |= 1ul << 55u;
            if (Default) _segment_descriptor |= 1ul << 54u;
            if (Present) _segment_descriptor |= 1ul << 47u;
            if (DescriptorPrivilegeLevel) _segment_descriptor |= 3ul << 45u;
            if (Conforming) _segment_descriptor |= 1ul << 42u;
            if (Readable) _segment_descriptor |= 1ul << 41u;
            if (Accessed) _segment_descriptor |= 1ul << 40u;

            _segment_descriptor |= (uint64_t) (limit >> 16u) << 48u;
            _segment_descriptor |= (uint64_t) (0xffffu & limit);

            _segment_descriptor |= (uint64_t) (base >> 24u) << 56u;
            _segment_descriptor |= (uint64_t) (0xffffffu & base) << 16u;
        }

        void set_code64(uint8_t Conforming, uint8_t Readable, uint8_t Accessed, uint8_t Granularity, uint8_t Default,
                        uint8_t LongMode, uint8_t Present, uint8_t DescriptorPrivilegeLevel) {
            _segment_descriptor = 3ul << 43u;

            if (Granularity) _segment_descriptor |= 1ul << 55u;
            if (Default) _segment_descriptor |= 1ul << 54u;
            if (LongMode) _segment_descriptor |= 1ul << 53u;
            if (Present) _segment_descriptor |= 1ul << 47u;
            if (DescriptorPrivilegeLevel) _segment_descriptor |= 3ul << 45u;
            if (Conforming) _segment_descriptor |= 1ul << 42u;
            if (Readable) _segment_descriptor |= 1ul << 41u;
            if (Accessed) _segment_descriptor |= 1ul << 40u;
        }

        void set(uint64_t desc) {
            _segment_descriptor = desc;
        }

        uint64_t segment_descriptor() {
            return _segment_descriptor;
        }
    };

    class SegmentDescriptorTable {
    private:
        SegmentDescriptor *segment_descriptor_table;
        uint64_t length = 0;
    public:
        SegmentDescriptorTable(void *offset) {
            segment_descriptor_table = (SegmentDescriptor *) offset;
        }

        __attribute__((always_inline)) inline void load_global_descriptor_table() {
            DTR gdtr = {(uint16_t) (sizeof(SegmentDescriptor) * length - 1), (uint64_t) segment_descriptor_table};

            __asm__ volatile (
            "lea rax, %0 \n"
            "lgdt [rax]"
            : : "m"(gdtr));
        }

        __attribute__((always_inline)) inline void set_segment(uint16_t cs, uint16_t ds, uint16_t ss) {

            __asm__ volatile (
            "mov ax, %0 \n"
            "mov ds, ax \n"
            "mov ax, %1 \n"
            "mov ss, ax"
            : : "m"(ds), "m"(ss)
            );


            void *a = &&ret;

            __asm__ volatile (
            "movzx eax, %0 \n"
            "push rax \n"
            "lea rax, +8[rsp] \n"
            "push rax \n"
            "pushfq \n"
            "movzx eax, %1 \n"
            "push rax \n"
            "push %2 \n"
            "iretq"
            : : "m"(ss), "m"(cs), "m"(a)
            );
            ret:
            return;
        }

        void push(SegmentDescriptor desc) {
            segment_descriptor_table[length++] = desc;
        }

        void push(uint64_t desc_uint) {
            SegmentDescriptor desc;
            desc.set(desc_uint);
            push(desc);
        }

        void push_data(uint32_t base, uint32_t limit, uint8_t ExpansionDirection, uint8_t Writeable, uint8_t Accessed,
                      uint8_t Granularity, uint8_t Big, uint8_t Present, uint8_t DescriptorPrivilegeLevel) {
            segment_descriptor_table[length ++].set_data(base, limit, ExpansionDirection, Writeable, Accessed, Granularity, Big, Present, DescriptorPrivilegeLevel);
        }

        void push_code(uint32_t base, uint32_t limit, uint8_t Conforming, uint8_t Readable, uint8_t Accessed,
                      uint8_t Granularity, uint8_t Default, uint8_t Present, uint8_t DescriptorPrivilegeLevel) {
            segment_descriptor_table[length ++].set_code(base, limit, Conforming, Readable, Accessed, Granularity, Default, Present, DescriptorPrivilegeLevel);
        }

        void push_code64(uint8_t Conforming, uint8_t Readable, uint8_t Accessed, uint8_t Granularity, uint8_t Default,
                        uint8_t LongMode, uint8_t Present, uint8_t DescriptorPrivilegeLevel) {
            segment_descriptor_table[length ++].set_code64(Conforming, Readable, Accessed, Granularity, Default, LongMode, Present, DescriptorPrivilegeLevel);
        }
    };
}

#endif //TIEOS_SEGMENTDESCRIPTORTABLE_H
