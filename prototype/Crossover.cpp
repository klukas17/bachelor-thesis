#include "stdlib.h"

#include "Crossover.h"

Unit* Crossover::perform(Unit* unit1, Unit* unit2) {
    Unit* new_unit = new Unit(unit1->codon_count);
    int delimiter = rand() % (unit1->codon_count - 2) + 1;
    for (int i = 0; i < new_unit->codon_count; i++) {
        if (i <= delimiter) new_unit->genome[i] = unit1->genome[i];
        else new_unit->genome[i] = unit2->genome[i];
    }
    return new_unit;
}