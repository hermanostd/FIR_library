#add executable file
add_executable(main main.cpp)

#link libraries
target_link_libraries(main PRIVATE easydsp)

#set compiler
target_compile_features(main PRIVATE cxx_std_23)