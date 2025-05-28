cmake_minimum_required(VERSION 3.15)
project(matcalc C)

set(CMAKE_C_STANDARD 90)

# sources
add_executable(matcalc
    mainmat.c
    mymat.c
)