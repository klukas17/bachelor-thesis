#include "stdlib.h"

#include "Crossover.h"
#include <iostream>

Unit* Crossover::perform(Unit* unit1, Unit* unit2) {
    if (unit1->codon_count != unit2->codon_count) {
        std::cerr << "Unmatching units in crossover!" << std::endl;
        exit(1);
    }

    Unit* new_unit = new Unit(unit1->codon_count);
    int delimiter = rand() % (unit1->codon_count - 2) + 1;
    for (int i = 0; i < new_unit->codon_count; i++) {
        if (i <= delimiter) new_unit->genome[i] = unit1->genome[i];
        else new_unit->genome[i] = unit2->genome[i];
    }
    return new_unit;
}