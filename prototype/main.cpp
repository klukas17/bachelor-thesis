#include <stdlib.h>

#include "GrammaticalEvolution.h"

int main() 
{
    srand(time(0));
    GrammaticalEvolution GE = GrammaticalEvolution();

    GE.population[0]->genome[0] = 2;
    GE.population[0]->genome[1] = 1;
    GE.population[0]->genome[2] = 1;
    GE.population[0]->genome[3] = 0;
    GE.population[0]->genome[4] = 0;
    GE.population[0]->genome[5] = 0;
    GE.population[0]->genome[6] = 1;
    GE.population[0]->genome[7] = 1;
    GE.population[0]->genome[8] = 1;
    GE.population[0]->genome[9] = 2;
    GE.population[0]->genome[10] = 0;
    GE.population[0]->genome[11] = 0;
    GE.population[0]->genome[12] = 0;
    GE.population[0]->genome[13] = 0;
    GE.population[0]->genome[14] = 0;
    GE.population[0]->genome[15] = 1;
    GE.population[0]->genome[16] = 1;
    GE.population[0]->genome[17] = 0;
    GE.population[0]->genome[18] = 0;
    GE.decode(GE.population[0]);

    /*
    GE.population[0].genome[0] = 0;
    GE.population[0].genome[1] = 0;
    GE.population[0].genome[2] = 1;
    GE.population[0].genome[3] = 1;
    GE.population[0].genome[4] = 1;
    GE.decode(GE.population[0]);
    */
}