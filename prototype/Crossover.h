#pragma once

#include "Unit.h"

class Crossover {
    public:
        
        Crossover();
        ~Crossover();

        Unit* perform(Unit* unit1, Unit* unit2);
};