cmake_minimum_required(VERSION 3.27)
project(lab2 C)

set(CMAKE_C_STANDARD 99)

add_executable(lab2 lab2.c
        mypcm.h
        mypcm.c)
