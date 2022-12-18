project(Enigma)

cmake_minimum_required(VERSION 3.22.1)

add_executable(enigma
    ../include/Plugboard.h
    ../include/Reflector.h
    ../include/Rotor.h
    ../src/main.cpp 
    ../src/Plugboard.cpp 
    ../src/Reflector.cpp 
    ../src/Rotor.cpp)