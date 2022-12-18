#pragma once

#include <string>
#include <vector>

class Plugboard
{
    public:
        Plugboard(std::vector<std::string> pairs);
        Plugboard() = default;
        char swap(char letter);

    private:
        std::vector<std::string> pairs;
};