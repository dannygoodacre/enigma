#pragma once

#include <string>
#include <vector>

class Rotor
{
    public:
        static const std::vector<std::string> allPermutations[12];

        static int mod(int a, int b);
        static char swapBetween(char letter, Rotor rotorIn, Rotor rotorOut);

        Rotor();
        Rotor(int number, char initRotorSetting, char initRingSetting);
        int getRotorSetting();
        void setRotorSetting(char rotorSetting);
        void tick();
        char swap(char letter, bool isMovingTowardReflector);

    private:
        int number;
        int initRotorSetting;
        int currentRotorSetting;
        int ringSetting;
        std::vector<std::string> permutations;
};