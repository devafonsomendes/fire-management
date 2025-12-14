cmake_minimum_required(VERSION 4.0)
project(LP_8250433_8250706 C)

set(CMAKE_C_STANDARD 90)

add_executable(LP_8250433_8250706 main.c
        firefighters.c
        equipments.c
        input.c
        occurrences.c
        interventions.c
        statistics.c)