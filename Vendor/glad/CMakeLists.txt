cmake_minimum_required(VERSION 3.20)
project(GLAD)

add_library(glad include/glad/glad.h src/glad.c)
target_include_directories(glad PUBLIC include/)
