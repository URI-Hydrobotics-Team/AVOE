#compiles the lib into a library and then combines it into the cmake thing 

#idk i used stack overflow to help with this lol

#UPDATE: yeah ig it creates a .a object file :P
add_library(lib ./lib.cpp ./clock.cpp ./network.cpp)


