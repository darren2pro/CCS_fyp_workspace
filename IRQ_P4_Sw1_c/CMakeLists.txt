cmake_minimum_required(VERSION 3.26)
project(IRQ_P4_Sw1_c C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(IRQ_P4_Sw1_c
        main.c
        main.h)
