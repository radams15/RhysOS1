cmake_minimum_required(VERSION 3.16)
project(RhysOS)

set(CMAKE_C_STANDARD 11)
set(CMAKE_SOURCE_DIR CPP)

include_directories(CPP)
include_directories(Headers)
include_directories(C_Interop)


add_executable(
        RhysOS
        CPP/Str.cpp
        CPP/Display.cpp
        CPP/Cpu/Interrupts.cpp
        CPP/Cpu/Io.cpp
        CPP/main.cpp
        CPP/Maths.cpp
        CPP/Serial.cpp
        CPP/Memory.cpp
        CPP/Cpu/isr.cpp
        CPP/Cpu/Gdt.cpp
        CPP/Cpu/Idt.cpp
        CPP/Cpu/Irq.cpp
        CPP/Clock.cpp
        CPP/Keyboard.cpp
        CPP/Str.cpp
        CPP/Mouse.cpp
        CPP/Queue.cpp

        C_Interop/stdio.c
)