cmake_minimum_required(VERSION 3.24)
project(C_Stuff C)

set(CMAKE_C_STANDARD 11)

add_executable(C_Stuff
        gcsheet.h
        lotto_gen.c
        process.c hexToBin.c)

add_executable(process process.c)
add_executable(lotto_gen lotto_gen.c)
add_executable(hexToBin hexToBin.c)