cmake_minimum_required(VERSION 3.15)
project(TieOS)

set(CMAKE_CXX_STANDARD 17)

include_directories(include/)

add_library(TieOS SHARED src/main.cpp src/GraphicsConfig.cpp src/stringlib.cpp src/mathlib.cpp src/MemoryMap.cpp src/cpu/SegmentDescriptor.cpp src/cpu/SegmentDescriptor.h src/interrupt.cpp include/interrupt.h src/cpu/InterruptDescriptorTable.h)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -nostdlib")
list(REMOVE_ITEM CMAKE_CXX_IMPLICIT_LINK_LIBRARIES stdc++)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -masm=intel")
