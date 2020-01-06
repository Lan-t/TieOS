cmake_minimum_required(VERSION 3.15)
project(TieOS)

set(CMAKE_CXX_STANDARD 17)

include_directories(include/)

add_library(TieOS SHARED
        src/main.cpp
        src/GraphicsConfig.cpp
        src/stringlib.cpp
        src/mathlib.cpp
        src/MemoryMap.cpp
        src/interrupt.cpp
        src/assembly/test.s
        )

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -nostdlib")
list(REMOVE_ITEM CMAKE_CXX_IMPLICIT_LINK_LIBRARIES stdc++)


set_target_properties(TieOS PROPERTIES PREFIX "")
set_target_properties(TieOS PROPERTIES OUTPUT_NAME "kernel")
set_target_properties(TieOS PROPERTIES SUFFIX ".elf")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -masm=intel")
