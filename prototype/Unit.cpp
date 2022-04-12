#include "Unit.h"

Unit::Unit(int c_c)
{
    codon_count = c_c;
    for (int i = 0; i < codon_count; i++)
    {
        genome.push_back(rand());
    }
}
Unit::~Unit(){}