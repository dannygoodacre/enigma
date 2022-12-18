#include "../include/Reflector.h"

Reflector::Reflector(int number) : Rotor(number + 8, 'A', 'A')
{
    return;
}

char Reflector::swap(char letter)
{
    return Rotor::swap(letter, true);
}