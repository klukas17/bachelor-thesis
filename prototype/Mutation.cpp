#include "stdlib.h"

#include "Mutation.h"

Mutation::Mutation(float m_r) {
    mutation_rate = m_r;
}

Mutation::~Mutation() {}

Unit* Mutation::perform(Unit* unit) {
    for (int i = 0; i < unit->codon_count; i++) {
        for (int MASK = 1; MASK < 256; MASK *= 2) {
            if ((rand() / (float) RAND_MAX) < mutation_rate) {
                unit->genome[i] = unit->genome[i] ^ MASK;
            }
        }
    }
    return unit;
}