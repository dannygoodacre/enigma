#include "../include/Plugboard.h"

Plugboard::Plugboard(std::vector<std::string> pairs)
{
    this->pairs = pairs;
}

// Return letter based on pair in pairs vector. If no pair, return letter.
char Plugboard::swap(char letter)
{
    bool found = false;
    std::string pair;
    int index;

    for (std::string p : this->pairs)
    {
        if ((index = p.find(letter)) != -1)
        {
            found = true;
            pair = p;
            break;
        }
    }

    return found ? pair[1 - index] : letter;
}