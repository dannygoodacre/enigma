# Enigma
An emulator of the Enigma encryption device.

## How it works
Please see [here](https://en.wikipedia.org/wiki/Enigma_machine) and [here](https://en.wikipedia.org/wiki/Enigma_rotor_details) for a thorough explanation of the mechanism which is simulated here computationally. 

### TL;DR
Each inputted letter is passed through three rotors, each with internal wiring to swap the letter to another. Another rotor at the end of the three (the reflector) sends to signal back through the rotors again for more swaps.

The three rotors (left, middle, and right) also behave like the hands of a clock (hour, minute, and second, respectively), which causes the alignment of each rotor to change before each inputted letter. In addition, there is a ring setting which causes further misalignment of the wiring, and a double stepping mechanism which causes rotors to sometimes 'tick' twice.

This means that for each set of rotor settings, we have a simple substitution cypher; but as the rotors tick the substitutions change. Therefore you must have the same settings at the start of the encryption process in order to decrypt a given message.

There is also a plugboard which makes further swaps based on how the user chooses to pair up letters. These swaps are made twice: right at the start and right at the end of the process.

## How to use the emulator

In `main.cpp` enter your chosen rotors, settings, and plugboard pairs. Then compile using the top-level directory's `CMakeLists.txt`.

The `test` directory contains the unit tests for the program. These can be run using the `CMakeLists.txt` within that directory.