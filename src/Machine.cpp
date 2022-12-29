#include "../include/Machine.h"
#include "../include/Rotor.h"
#include "../include/Reflector.h"
#include "../include/Plugboard.h"

#include <string>

Machine::Machine(const Rotor &leftRotor, const Rotor &middleRotor, 
    const Rotor &rightRotor, const Reflector &reflector,
    const Plugboard &plugboard) 
        : leftRotor(leftRotor), middleRotor(middleRotor), 
        rightRotor(rightRotor), reflector(reflector), plugboard(plugboard)
{
    this->staticRotor = Rotor();
}

// Return letter after passing through machine swaps.
char Machine::swap(char letter)
{
    this->step();
    letter = this->plugboard.swap(letter);
    letter = Rotor::swapBetween(letter, this->staticRotor, this->rightRotor);
    letter = this->rightRotor.swap(letter, true);
    letter = Rotor::swapBetween(letter, this->rightRotor, this->middleRotor);
    letter = this->middleRotor.swap(letter, true);
    letter = Rotor::swapBetween(letter, this->middleRotor, this->leftRotor);
    letter = this->leftRotor.swap(letter, true);
    letter = Rotor::swapBetween(letter, this->leftRotor, this->reflector);
    letter = reflector.swap(letter);
    letter = Rotor::swapBetween(letter, this->reflector, this->leftRotor);
    letter = this->leftRotor.swap(letter, false);
    letter = Rotor::swapBetween(letter, this->leftRotor, this->middleRotor);
    letter = this->middleRotor.swap(letter, false);
    letter = Rotor::swapBetween(letter, this->middleRotor, this->rightRotor);
    letter = this->rightRotor.swap(letter, false);
    letter = Rotor::swapBetween(letter, this->rightRotor, this->staticRotor);
    return this->plugboard.swap(letter);
}

// Apply char swap sequentially to a string. Return swapped string.
std::string Machine::swap(std::string str)
{
    // TODO: include ticks
    for (int i = 0; str[i]; i++)
        str[i] = this->swap(str[i]);
    return str;
}

// Increment rotor positions.
void Machine::step()
{
    // TODO: double stepping
    this->rightRotor.tick();

    if (this->rightRotor.getRotorSetting() == 26)
    {
        this->rightRotor.setRotorSetting(0);
        this->middleRotor.tick();
    }
    if (this->middleRotor.getRotorSetting() == 26)
    {
        this->middleRotor.setRotorSetting(0);
        this->leftRotor.tick();
    }
    if (this->leftRotor.getRotorSetting() == 26)
    {
        this->leftRotor.setRotorSetting(0);
    }
}

void Machine::resetRotorSettings()
{
    this->leftRotor.resetRotorSetting();
    this->middleRotor.resetRotorSetting();
    this->rightRotor.resetRotorSetting();
}