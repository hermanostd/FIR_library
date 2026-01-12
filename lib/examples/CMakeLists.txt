cmake_minimum_required(VERSION 3.25)

add_executable(example1 example1.cpp)

#set required cxx standard
set_property(TARGET example1 PROPERTY CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

#link libraries
target_link_libraries(example1 PRIVATE easydsp)

add_executable(example2 example2.cpp)
set_property(TARGET example2 PROPERTY CXX_STANDARD 23)
target_link_libraries(example2 PRIVATE easydsp)

add_executable(example3 example3.cpp)
set_property(TARGET example3 PROPERTY CXX_STANDARD 23)
target_link_libraries(example3 PRIVATE easydsp)

add_executable(example4 example4.cpp)
set_property(TARGET example4 PROPERTY CXX_STANDARD 23)
target_link_libraries(example4 PRIVATE easydsp)