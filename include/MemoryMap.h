//
// Created by tia on 2020/01/02.
//

#ifndef TIEOS_MEMORYMAP_H
#define TIEOS_MEMORYMAP_H


#include <cstdint>

#include "GraphicsConfig.h"


namespace memory_map {

    enum EFI_MEMORY_TYPE {
        EfiReservedMemoryType,
        EfiLoaderCode,
        EfiLoaderData,
        EfiBootServicesCode,
        EfiBootServicesData,
        EfiRuntimeServicesCode,
        EfiRuntimeServicesData,
        EfiConventionalMemory,
        EfiUnusableMemory,
        EfiACPIReclaimMemory,
        EfiACPIMemoryNVS,
        EfiMemoryMappedIO,
        EfiMemoryMappedIOPortSpace,
        EfiPalCode,
        EfiPersistentMemory,
        EfiMaxMemoryType
    };

    struct EFI_MEMORY_DESCRIPTOR {
        EFI_MEMORY_TYPE Type;
        void *PhysicalStart;
        void *VirtualStart;
        uint64_t NumberOfPages;
        uint64_t Attribute;
    };

    struct _MemoryMap {
        uint64_t memory_map_size;
        EFI_MEMORY_DESCRIPTOR *memory_map;
        uint64_t map_key;
        uint64_t descriptor_size;
        uint32_t descriptor_version;
    };

    class MemoryMap {
    private:
        uint64_t memory_map_size;
        EFI_MEMORY_DESCRIPTOR *memory_map;
        uint64_t map_key;
        uint64_t descriptor_size;
        uint32_t descriptor_version;

        static const char* get_memory_type(EFI_MEMORY_TYPE type);
        static int is_usable_memory_type(EFI_MEMORY_TYPE type);

    public:
        MemoryMap() {};
        MemoryMap(_MemoryMap *memoryMap);
        void put_memory_info(graphics_config::GraphicsConfig graphicsConfig);
    };

}

#endif //TIEOS_MEMORYMAP_H
