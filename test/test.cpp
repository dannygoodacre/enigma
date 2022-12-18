#include "../include/Rotor.h"
#include "../include/Reflector.h"
#include "../include/Plugboard.h"

#include <iostream>

#define IS_TRUE(x) { if (!(x)) std::cout << __FUNCTION__ << " failed on line " \
    << __LINE__ << std::endl; }

void test_RotorSwap_1AA()
{
    Rotor rotor(1, 'A', 'A');
    IS_TRUE(rotor.swap('A', true) == 'E');
    IS_TRUE(rotor.swap('E', false) == 'A');
    IS_TRUE(rotor.swap('C', true) == 'M');
}

void test_RotorSwap_1AE()
{
    Rotor rotor(1, 'A', 'E');
    IS_TRUE(rotor.swap('A', true) == 'L');
    IS_TRUE(rotor.swap('L', false) == 'A');
    IS_TRUE(rotor.swap('C', true) == 'D');
}

void test_RotorSwapBetween_from1BA_to2GA()
{
    // Ring setting has no bearing on swapping between.
    Rotor r1(1, 'B', 'A');
    Rotor r2(2, 'G', 'A');
    IS_TRUE(Rotor::swapBetween('A', r1, r2) == 'V');
    IS_TRUE(Rotor::swapBetween('V', r2, r1) == 'A');

    IS_TRUE(Rotor::swapBetween('M', r1, r2) == 'H');
    IS_TRUE(Rotor::swapBetween('H', r2, r1) == 'M');
}

void test_RotorSwapBetween_fromStaticRotor_to1GC()
{
    Rotor s = Rotor();
    Rotor r(1, 'G', 'C');
    IS_TRUE(Rotor::swapBetween('A', s, r) == 'U');
    IS_TRUE(Rotor::swapBetween('U', r, s) == 'A');

    IS_TRUE(Rotor::swapBetween('Z', s, r) == 'T');
    IS_TRUE(Rotor::swapBetween('T', r, s) == 'Z');
}

void test_ReflectorSwap_2()
{
    Reflector ref(2);
    IS_TRUE(ref.swap('F') == 'S');
    IS_TRUE(ref.swap('I') == 'P');
}

void test_PlugboardSwap_AB()
{
    Plugboard p({"AB"});
    IS_TRUE(p.swap('A') == 'B');
    IS_TRUE(p.swap('B') == 'A');
    IS_TRUE(p.swap('C') == 'C');    
}

int main()
{
    test_RotorSwap_1AA();
    test_RotorSwap_1AE();
    test_ReflectorSwap_2();
    test_RotorSwapBetween_from1BA_to2GA();
    test_RotorSwapBetween_fromStaticRotor_to1GC();
    test_PlugboardSwap_AB();
    return 0;
}