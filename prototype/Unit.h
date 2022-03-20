#pragma once

#include <stdlib.h>

class Unit
{
    public:

        unsigned char* genome;

        Unit(int codon_count)
        {
            genome = (unsigned char*) malloc(sizeof(unsigned char) * codon_count);
            for (int i = 0; i < codon_count; i++)
            {
                this->genome[i] = rand();
            }
        }
        ~Unit(){}
};