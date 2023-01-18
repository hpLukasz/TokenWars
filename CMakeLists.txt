cmake_minimum_required(VERSION 3.10)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# set the project name
project(tokenwar)

file(GLOB SOURCES
    headers/*.h
    src/*.cpp
)

include_directories(include)

add_executable(tokenwar ${SOURCES})
TARGET_LINK_LIBRARIES( tokenwar pthread)