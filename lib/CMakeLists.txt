cmake_minimum_required(VERSION 3.23)    #specify required version for cmake

project(easydsp VERSION 0.1.1 LANGUAGES CXX)

# Library target
add_library(easydsp)

# C++ standard
target_compile_features(easydsp PUBLIC cxx_std_23)

# Include directories
target_include_directories(easydsp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Source files
target_sources(easydsp PRIVATE
    src/FIR.cpp
    src/WindowLowpass.cpp
    src/WindowHighpass.cpp
    src/WindowBandpass.cpp
    src/FrequencySampling.cpp
)

# Examples
add_subdirectory(examples)