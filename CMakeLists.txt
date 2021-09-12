cmake_minimum_required(VERSION 3.20)
project(BinPacking_OMP)

FIND_PACKAGE( OpenMP REQUIRED)
if(OPENMP_FOUND)
    message("OPENMP FOUND")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

set(CMAKE_CXX_STANDARD 20)

add_executable(BinPacking_OMP main.cpp LowerBound.cpp LowerBound.h UpperBound.cpp UpperBound.h DataInput.h DataInput.cpp Algorithm.cpp Algorithm.h Bin.cpp Bin.h)