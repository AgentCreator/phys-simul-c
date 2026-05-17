cmake_minimum_required(VERSION 4.2)
project(simulc C)

set(CMAKE_C_STANDARD 23)

add_executable(simulc main.c
        vector.h
        vector.c)
