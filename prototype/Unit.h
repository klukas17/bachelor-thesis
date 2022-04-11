#pragma once

#include <stdlib.h>

class Unit
{
    public:

        unsigned char* genome;
        int codon_count;

        Unit(int codon_count);
        ~Unit();
};