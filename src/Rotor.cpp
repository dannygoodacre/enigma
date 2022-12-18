#include "../include/Rotor.h"

const std::vector<std::string> Rotor::allPermutations[12] = 
{
    {"AELTPHQXRU","BKNW","CMOY","DFG","IV","JZ","S"}, 
    {"FIXVYOMW","CDKLHUP","ESZ","BJ","GR","NT","A","Q"}, 
    {"ABDHPEJT","CFLVMZOYQIRWUKXSG","N"}, 
    {"AEPLIYWCOXMRFZBSTGJQNH","DV","KU"}, 
    {"AVOLDRWFIUQ","BZKSMNHYC","EGTJPX"}, 
    {"AJQDVLEOZWIYTS","CGMNHFUX","BPRK"}, 
    {"ANOUPFRIMBZTLWKSVEGCJYDHXQ"}, 
    {"AFLSETWUNDHOZVICQ","BKJ","GXY","MPR"},
    // Reflector permutations
    {"AE","BJ","CM","DZ","FL","GY","HX","IV","KW","NR","OQ","PU","ST"},
    {"AY","BR","CU","DH","EQ","FS","GL","IP","JX","KN","MO","TZ","VW"},
    {"AF","BV","CP","DJ","EI","GO","HY","KR","LZ","MX","NW","TQ","SU"},
    // Static rotor trivial permutation
    {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O",
        "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"}
};

int Rotor::mod(int a, int b)
{
    while (a < 0)
        a += b;
    return a % b;
}

char Rotor::swapBetween(char letter, Rotor rotorIn, Rotor rotorOut)
{
    return mod(letter - 65 + rotorIn.getRotorSetting() 
        - rotorOut.getRotorSetting(), 26) + 65;
}

Rotor::Rotor()
{
    this->number = 12;
    this->initRotorSetting = 1;
    this->currentRotorSetting = 1;
    this->ringSetting = 0;
    this->permutations = allPermutations[11];
}

Rotor::Rotor(int number, char initRotorSetting, char ringSetting)
{
    this->number = number;
    this->initRotorSetting = initRotorSetting - 64;
    this->currentRotorSetting = initRotorSetting - 64;
    this->ringSetting = ringSetting - 65;
    this->permutations = allPermutations[number - 1];
}

int Rotor::getRotorSetting()
{
    return this->currentRotorSetting;
}

void Rotor::setRotorSetting(char rotorSetting)
{
    this->currentRotorSetting = rotorSetting;
}

void Rotor::tick()
{
    this->currentRotorSetting++;
}

char Rotor::swap(char letter, bool isMovingTowardReflector)
{
    // TODO: Explain the mathematics behind this function.
    int index, len;
    std::string permutation;
    letter += isMovingTowardReflector * this->ringSetting;

    // Find permutation containing letter.
    for (std::string perm : this->permutations)
    {
        if ((index = perm.find(letter)) != -1)
        {
            len = (permutation = perm).length();
            break;
        }
    }
    index += isMovingTowardReflector ? 1 : -1;

    return permutation[mod(index, len)] 
        - !isMovingTowardReflector*this->ringSetting;
}