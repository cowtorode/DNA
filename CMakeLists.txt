cmake_minimum_required(VERSION 3.26)
project(DNA)

set(CMAKE_CXX_STANDARD 17)

add_executable(DNA src/main.cpp
        src/util/stringutil.cpp
        src/util/stringutil.h
        src/dna/nucleicacid.cpp
        src/dna/nucleicacid.h)
