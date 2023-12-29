cmake_minimum_required(VERSION 3.16.3)

project(AoL)

add_executable(${PROJECT_NAME} main.c)
add_compile_definitions("BUILT_USING_CMAKE")