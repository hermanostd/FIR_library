#thanks YT:@PunchedTape for CMake tutorial :D

cmake_minimum_required(VERSION 3.25)    #specify required version for cmake

#project name
project(easydsp)

# Library target
add_library(${PROJECT_NAME})

#set required cxx standard
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 23)
# set(CMAKE_CXX_STANDARD 23) smh this doesn't work??
set(CMAKE_CXX_STANDARD_REQUIRED YES)

# Include directories
target_include_directories(easydsp
     PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Source files
target_sources(easydsp PRIVATE
    src/FIR.cpp
    src/WindowLowpass.cpp
    src/WindowHighpass.cpp
    src/WindowBandpass.cpp
    src/FrequencySampling.cpp
    src/Window.cpp
)

# Examples
add_subdirectory(examples)