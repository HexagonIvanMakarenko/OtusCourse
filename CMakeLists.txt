cmake_minimum_required(VERSION 3.16)

project(helloworld)

configure_file(src/version.h.in src/version.h)

add_executable(ip_filtration src/ip_filter.cpp)

add_executable(helloworld src/helloworld.cpp)

install(TARGETS helloworld)