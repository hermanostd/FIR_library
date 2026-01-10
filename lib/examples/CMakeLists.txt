cmake_minimum_required(VERSION 3.25)

add_executable(example1 example1.cpp)

#set required cxx standard
set_property(TARGET example1 PROPERTY CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

#link libraries
target_link_libraries(example1 PRIVATE easydsp)