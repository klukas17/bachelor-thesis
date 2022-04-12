#pragma once

#include <stdlib.h>
#include <vector>

class Unit
{
    public:

        std::vector<unsigned char> genome;
        int codon_count;

        Unit(int codon_count);
        ~Unit();
};