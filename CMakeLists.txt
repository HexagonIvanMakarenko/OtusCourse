cmake_minimum_required(VERSION 3.16)

project(helloworld)

add_executable(helloworld ${CMAKE_CURRENT_SOURCE_DIR}/helloworld.cpp)

install(TARGETS helloworld)