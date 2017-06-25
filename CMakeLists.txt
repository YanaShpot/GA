cmake_minimum_required(VERSION 3.7)
project(MyGA)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES MyAlgo/main.cpp MyAlgo/Chromosome.cpp MyAlgo/GeneticAlgo.cpp MyAlgo/Log.cpp MyAlgo/Population.cpp)
add_executable(MyGA ${SOURCE_FILES})