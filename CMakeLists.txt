cmake_minimum_required(VERSION 2.8.4)
project(distributed_kmeans)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "~/ClionProjects/distributed_kmeans/bin")

set(SOURCE_FILES main.cpp
    src/api/point.hpp
    src/api/cluster.hpp
    src/util/cmdopts.hpp
    src/util/cmdopts.cpp
    src/algorithms/kmeans.cpp
    src/algorithms/kmeans.hpp)
add_executable(distributed_kmeans ${SOURCE_FILES})