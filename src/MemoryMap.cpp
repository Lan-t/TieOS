//
// Created by tia on 2020/01/02.
//

#include <cstdint>

#include "MemoryMap.h"
#include "stringlib.h"

namespace memory_map {

    const char *MemoryMap::get_memory_type(EFI_MEMORY_TYPE type) {
        switch (type) {
            case EfiReservedMemoryType:
                return "EfiReservedMemoryType";
            case EfiLoaderCode:
                return "EfiLoaderCode";
            case EfiLoaderData:
                return "EfiLoaderData";
            case EfiBootServicesCode:
                return "EfiBootServicesCode";
            case EfiBootServicesData:
                return "EfiBootServicesData";
            case EfiRuntimeServicesCode:
                return "EfiRuntimeServicesCode";
            case EfiRuntimeServicesData:
                return "EfiRuntimeServicesData";
            case EfiConventionalMemory:
                return "EfiConventionalMemory";
            case EfiUnusableMemory:
                return "EfiUnusableMemory";
            case EfiACPIReclaimMemory:
                return "EfiACPIReclaimMemory";
            case EfiACPIMemoryNVS:
                return "EfiACPIMemoryNVS";
            case EfiMemoryMappedIO:
                return "EfiMemoryMappedIO";
            case EfiMemoryMappedIOPortSpace:
                return "EfiMemoryMappedIOPortSpace";
            case EfiPalCode:
                return "EfiPalCode";
            case EfiPersistentMemory:
                return "EfiPersistentMemory";
            case EfiMaxMemoryType:
                return "EfiMaxMemoryType";
            default:
                return "InvalidMemoryType";
        }
    }

    int MemoryMap::is_usable_memory_type(EFI_MEMORY_TYPE type) {
        switch (type) {
            case EfiReservedMemoryType:
                return 0;
            case EfiLoaderCode:
                return 0;
            case EfiLoaderData:
                return 0;
            case EfiBootServicesCode:
                return 1;
            case EfiBootServicesData:
                return 1;
            case EfiRuntimeServicesCode:
                return 0;
            case EfiRuntimeServicesData:
                return 0;
            case EfiConventionalMemory:
                return 1;
            case EfiUnusableMemory:
                return 0;
            case EfiACPIReclaimMemory:
                return 0;
            case EfiACPIMemoryNVS:
                return 0;
            case EfiMemoryMappedIO:
                return 0;
            case EfiMemoryMappedIOPortSpace:
                return 0;
            case EfiPalCode:
                return 0;
            case EfiPersistentMemory:
                return 0;
            case EfiMaxMemoryType:
                return 0;
            default:
                return 0;
        }
    }

    MemoryMap::MemoryMap(memory_map::_MemoryMap *memoryMap) {
        memory_map_size = memoryMap->memory_map_size;
        memory_map = memoryMap->memory_map;
        map_key = memoryMap->map_key;
        descriptor_size = memoryMap->descriptor_size;
        descriptor_version = memoryMap->descriptor_version;
    }

    void MemoryMap::put_memory_info(graphics_config::GraphicsConfig graphicsConfig) {
        EFI_MEMORY_DESCRIPTOR *iter;
        uint64_t i = 0;
        uint64_t x = 0, y = 0;
        for (iter = memory_map;
             (uint64_t) iter < (uint64_t) memory_map + memory_map_size; iter = (EFI_MEMORY_DESCRIPTOR *) (
                (uint64_t) iter + descriptor_size), i++) {
            char start_addr_buf[17], end_addr_buf[17], size_buff[17];
            tiestd::itoa((uint64_t) iter->PhysicalStart, start_addr_buf, 17, 16,
                         tiestd::FILL_ZERO | tiestd::SET_NULL_TERMINATE);
            tiestd::itoa((uint64_t) iter->PhysicalStart + iter->NumberOfPages * 0x1000 - 1, end_addr_buf, 17, 16,
                         tiestd::FILL_ZERO | tiestd::SET_NULL_TERMINATE);
            tiestd::itoa((uint64_t) iter->NumberOfPages * 0x1000, size_buff, 17, 16,
                         tiestd::FILL_ZERO | tiestd::SET_NULL_TERMINATE);
            uint32_t color = 0xffffffff;
            if (is_usable_memory_type(iter->Type)) {
                color = 0xffffff00;
            }
            graphicsConfig.put_strings(x, y++, color, start_addr_buf, " - ", end_addr_buf, " : ", size_buff, " : ",
                                       get_memory_type(iter->Type),
                                       nullptr);
        }

        char func_addr_buf[17], var_addr_buf[17], frame_buffer_addr_buf[17];
        tiestd::itoa((uint64_t) var_addr_buf, var_addr_buf, 17, 16,
                     tiestd::SET_NULL_TERMINATE | tiestd::FILL_ZERO);

        graphicsConfig.put_strings(x, ++y, 0xffffffff, "var:var_addr_buf:          ", var_addr_buf, nullptr);
    }
}

