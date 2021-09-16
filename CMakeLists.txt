cmake_minimum_required(VERSION 3.20)
project(example C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(
        example
        elevetor.c
        scenario.h
        scenario1.c
        scenario2.c
        scenario3.c func.c func.h)
