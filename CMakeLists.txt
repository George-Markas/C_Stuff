cmake_minimum_required(VERSION 3.24)
project(C_Stuff C)

set(CMAKE_C_STANDARD 11)

add_executable(C_Stuff
        glib/glib.c
        lottoGen.c
        process.c glib/glib.h)

add_executable(process process.c)
add_executable(lotto_gen lottoGen.c)
add_executable(hexToBin hexBin.c)