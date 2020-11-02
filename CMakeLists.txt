cmake_minimum_required(VERSION 3.16)
project(RhysOS)

set(CMAKE_C_STANDARD 11)
set(CMAKE_SOURCE_DIR C)

include_directories(C)
include_directories(Headers)

add_executable(
        RhysOS
        C/String.cpp
        C/Display.cpp
        C/Cpu/Interrupts.cpp
        C/Cpu/Io.cpp
        C/main.cpp
        C/Maths.cpp
        C/Serial.cpp
        C/Memory.cpp
        C/Cpu/isr.cpp
        C/Cpu/Gdt.cpp
        C/Cpu/Idt.cpp
        C/Cpu/Irq.cpp
        C/Clock.cpp
        C/Keyboard.cpp
        C/Mouse.cpp)