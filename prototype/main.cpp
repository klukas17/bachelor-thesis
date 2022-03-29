#include <stdlib.h>

#include "GrammaticalEvolution.h"
#include "Strategy.h"
#include "FIFO.h"
#include "OPT.h"
#include "LFU.h"
#include "LRU.h"
#include "CLOCK.h"

int PAGE_COUNT = 8;
int FRAME_COUNT = 3;

int main() 
{
    srand(time(0));
    /*
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

     */
    /*
    GE.population[0].genome[0] = 0;
    GE.population[0].genome[1] = 0;
    GE.population[0].genome[2] = 1;
    GE.population[0].genome[3] = 1;
    GE.population[0].genome[4] = 1;
    GE.decode(GE.population[0]);
    */

   std::vector<int> requests;
   std::ifstream in("zahtjevi_sanity_check.txt");
   std::string line, segment;

    for (;getline(in, line);) {
        std::stringstream s(line);
        while (getline(s, segment, ' ')) {
            requests.push_back(stoi(segment));
        }
    }

    std::cout << requests.size() << std::endl;

    /*
    Strategy* s1 = new FIFO(requests, PAGE_COUNT, FRAME_COUNT);
    std::cout << "FIFO" << std::endl;
    std::cout << "-------------------------------" << std::endl;
    s1->simulate();
    std::cout << "-------------------------------" << std::endl;
    std::cout << s1->requests.size() << " " << s1->hits << " " << s1->misses << " " << s1->page_count << " " << s1->frame_count << std::endl;
    */
    /*
    Strategy* s2 = new LFU(requests, PAGE_COUNT, FRAME_COUNT);
    std::cout << "LFU" << std::endl;
    std::cout << "-------------------------------" << std::endl;
    s2->simulate();
    std::cout << "-------------------------------" << std::endl;
    std::cout << s2->requests.size() << " " << s2->hits << " " << s2->misses << " " << s2->page_count << " " << s2->frame_count << std::endl;
    */
    Strategy* s3 = new LRU(requests, PAGE_COUNT, FRAME_COUNT);
    std::cout << "LRU" << std::endl;
    std::cout << "-------------------------------" << std::endl;
    s3->simulate();
    std::cout << "-------------------------------" << std::endl;
    std::cout << s3->requests.size() << ": " << s3->hits << " " << s3->misses << " " << s3->page_count << " " << s3->frame_count << std::endl;
    /*
    Strategy* s4 = new CLOCK(requests, PAGE_COUNT, FRAME_COUNT);
    std::cout << "CLOCK" << std::endl;
    std::cout << "-------------------------------" << std::endl;
    s4->simulate();
    std::cout << "-------------------------------" << std::endl;
    std::cout << s4->requests.size() << " " << s4->hits << " " << s4->misses << " " << s4->page_count << " " << s4->frame_count << std::endl;
    */
    /*
    Strategy* s5 = new OPT(requests, PAGE_COUNT, FRAME_COUNT);
    std::cout << "OPT" << std::endl;
    std::cout << "-------------------------------" << std::endl;
    s5->simulate();
    std::cout << "-------------------------------" << std::endl;
    std::cout << s5->requests.size() << " " << s5->hits << " " << s5->misses << " " << s5->page_count << " " << s5->frame_count << std::endl;
    */
}