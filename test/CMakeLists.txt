project(EnigmaTest)

# Running this application will run the unit tests for the program.

cmake_minimum_required(VERSION 3.22.1)

add_executable(testenigma
    ../include/Plugboard.h
    ../include/Reflector.h
    ../include/Rotor.h
    test.cpp 
    ../src/Plugboard.cpp 
    ../src/Reflector.cpp 
    ../src/Rotor.cpp)