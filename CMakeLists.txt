cmake_minimum_required(VERSION 3.24)
project(C_Stuff C)

set(CMAKE_C_STANDARD 11)

add_executable(C_Stuff
        b447.c
        lottoGen.c
        process.c b447.h scratchFile.c)

add_executable(process process.c)
add_executable(lottoGen lottoGen.c)
add_executable(hexBin hexBin.c)
add_executable(scratchFile scratchFile.c)