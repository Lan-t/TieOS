#ifndef TIEOS_MAIN_H
#define TIEOS_MAIN_H

#include "GraphicsConfig.h"
#include "MemoryMap.h"
#include "interrupt.h"



extern graphics_config::GraphicsConfig gGraphicsConfig;
extern memory_map::MemoryMap gMemoryMap;



extern "C" {
void _start(graphics_config::_GraphicsConfig *graphicsConfig, memory_map::_MemoryMap *memoryMap);
};

#endif //TIEOS_MAIN_H