cmake_minimum_required(VERSION 3.7)
project(GA)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Chromosome.cpp Chromosome.h Gene_impl.hpp Gene.h GeneBit.cpp GeneBit.h GeneStr.cpp GeneStr.h Population.cpp Population.h)
add_executable(GA ${SOURCE_FILES})