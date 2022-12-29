#pragma once

#include "Rotor.h"
#include "Reflector.h"
#include "Plugboard.h"

#include <string>

class Machine
{
    public:
        Machine(const Rotor &leftRotor, const Rotor &middleRotor, 
            const Rotor &rightRotor, const Reflector &reflector, 
            const Plugboard &plugboard);
        char swap(char letter);
        std::string swap(std::string str);
        void step();
        void resetRotorSettings();

    private:
        Rotor staticRotor;
        Rotor leftRotor;
        Rotor middleRotor;
        Rotor rightRotor;
        Reflector reflector;
        Plugboard plugboard;
};