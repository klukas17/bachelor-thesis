#include <stdlib.h>

#include "GrammaticalEvolution.h"
#include "Strategy.h"
#include "FIFO.h"
#include "OPT.h"
#include "LRU.h"
#include "CLOCK.h"

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
    std::cout << GE.decode(GE.population[0]) << std::endl;

    /*
    GE.population[0].genome[0] = 0;
    GE.population[0].genome[1] = 0;
    GE.population[0].genome[2] = 1;
    GE.population[0].genome[3] = 1;
    GE.population[0].genome[4] = 1;
    GE.decode(GE.population[0]);
    */

   std::vector<int> requests;
   std::ifstream in("zahtjevi_treniranje.txt");
   std::string line, segment;

    for (;getline(in, line);) {
        std::stringstream s(line);
        while (getline(s, segment, ' ')) {
            requests.push_back(stoi(segment));
        }
    }

    std::cout << requests.size() << std::endl;

    Strategy* s1 = new FIFO(requests);
    Strategy* s2 = new LRU(requests);
    Strategy* s3 = new CLOCK(requests);
    Strategy* s4 = new OPT(requests);
    s1->simulate();
    s2->simulate();
    s3->simulate();
    s4->simulate();

    std::cout << s1->requests.size() << " " << s1->hits << " " << s1->misses << std::endl;
    std::cout << s2->requests.size() << " " << s2->hits << " " << s2->misses << std::endl;
    std::cout << s3->requests.size() << " " << s3->hits << " " << s3->misses << std::endl;
    std::cout << s4->requests.size() << " " << s4->hits << " " << s4->misses << std::endl;
}