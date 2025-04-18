cmake_minimum_required(VERSION 3.30)
project(magic C)

set(CMAKE_C_STANDARD 90)

add_executable(magic main.c magic.c input.c
        output.c)




