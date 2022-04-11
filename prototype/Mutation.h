#pragma once

#include "Unit.h"

class Mutation {
    public:
        float mutation_rate;

        Mutation(float m_r);
        ~Mutation();

        Unit* perform(Unit* unit);
};