cmake_minimum_required (VERSION 3.12.4)
project (test)

#
# I use the C++ 11 extensions
# Also, I want warnings treated as errors, and be fairly pedantic
#
set(CMAKE_CXX_STANDARD 11) # C++11...
set(CMAKE_CXX_STANDARD_REQUIRED ON) #...is required...
set(CMAKE_CXX_EXTENSIONS OFF) #...without compiler extensions like gnu++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra -Werror")

#
# Put the binaries into "bin/"
#
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin/")

#
# set default build to debug
#
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build" FORCE)
endif(NOT CMAKE_BUILD_TYPE)

include_directories(include)
add_subdirectory(packages/gflags)

#
# Lesson 14 - Binary Search Algorithm - MinMaxDivision
#
add_executable (MinMaxDivisionTest src/MinMaxDivisionTest.cpp ../Lesson\ 14\ -\ Binary\ Search\ Algorithm/MinMaxDivision.cpp)
target_link_libraries(MinMaxDivisionTest gflags::gflags)
