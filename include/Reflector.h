#pragma once

#include "Rotor.h"

class Reflector : public Rotor
{
    public:
        Reflector(int number);
        char swap(char letter);

    private:
        std::vector<std::string> pairs;
};