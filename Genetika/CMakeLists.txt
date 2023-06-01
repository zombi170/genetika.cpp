cmake_minimum_required(VERSION 3.21)
project(Genetika)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Genetika
        allapotgep.cpp
        allapotgep.h
        genetika_teszt.cpp
        gtest_lite.h
        memtrace.cpp
        memtrace.h)
