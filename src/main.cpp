#include "../include/Rotor.h"
#include "../include/Reflector.h"
#include "../include/Machine.h"

#include <iostream>

int main()
{
    Rotor leftRotor(3, 'A', 'A');
    Rotor middleRotor(2, 'A', 'A');
    Rotor rightRotor(1, 'A', 'A');
    Reflector ref(1);
    Plugboard plugboard({"AB"});
    Machine m(leftRotor, middleRotor, rightRotor, ref, plugboard);
    
    // TODO: Add input validation.
    char choice;
    std::string str;
    while (choice != 'X')
    {
        std::cout << "S - Swap\n";
        std::cout << "R - Reset rotor settings\n";
        std::cout << "X - Exit\n";
        std::cout << "Choice: ";
        std::cin >> choice;
        switch (choice = toupper(choice))
        {
            case 'S':
                std::cout << "String: ";
                std::cin >> str;
                for (auto &c : str) c = toupper(c);
                std::cout << str << "-->" << m.swap(str) << "\n\n";
                break;
            case 'R':
                m.resetRotorSettings();
                std::cout << "Rotor settings reset.\n\n";
            case 'X':
                break;
        }
    }
    std::cout << "Goodbye!\n";
    return 0;
}