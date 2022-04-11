#include "Unit.h"

Unit::Unit(int c_c)
{
    codon_count = c_c;
    genome = (unsigned char*) malloc(sizeof(unsigned char) * codon_count);
    for (int i = 0; i < codon_count; i++)
    {
        genome[i] = rand();
    }
}
Unit::~Unit(){}