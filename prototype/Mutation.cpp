#include "stdlib.h"

#include "Mutation.h"

float MUTATION_RATE = 0.001;

Unit* Mutation::perform(Unit* unit) {
    for (int i = 0; i < unit->codon_count; i++) {
        for (char MASK=1; MASK < 256; MASK *= 2) {
            if (rand() / float(RAND_MAX) < MUTATION_RATE) {
                unit->genome[i] = unit->genome[i] ^ MASK;
            }
        }
    }
    return unit;
}