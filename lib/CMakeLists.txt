cmake_minimum_required(VERSION 3.23)

project(EasyDSP
    VERSION 0.1.0
    LANGUAGES CXX
)

# -----------------------------
# Library target
# -----------------------------
add_library(EasyDSP)

# C++ standard
target_compile_features(easydsp PUBLIC cxx_std_23)

# Include directories
target_include_directories(EasyDSP
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Source files
target_sources(EasyDSP
    PRIVATE
        src/FIR.cpp
        src/Lowpass.cpp
        src/Highpass.cpp
        src/Bandpass.cpp
)

# Warnings (recommended)
target_compile_options(easydsp PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

# -----------------------------
# Examples
# -----------------------------
add_subdirectory(examples)