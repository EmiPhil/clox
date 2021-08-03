cmake_minimum_required(VERSION 3.19)
project(clox C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(clox
        main.c
        main.h
        common.h
        memory.c
        memory.h
        chunk.c
        chunk.h debug.c debug.h value.c value.h vm.c vm.h compiler.c compiler.h scanner.c scanner.h object.c object.h table.c table.h)