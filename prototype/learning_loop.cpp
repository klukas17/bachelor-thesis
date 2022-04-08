#include <stdlib.h>

#include "GrammaticalEvolution.h"

int PAGE_COUNT = 0;
int FRAME_COUNT = 0;
int POPULATION_COUNT = 0;

int main(int argc, char* argv[]) {
    PAGE_COUNT = std::stoi(argv[1]);
    FRAME_COUNT = std::stoi(argv[2]);
    POPULATION_COUNT = std::stoi(argv[3]);

    std::cout << PAGE_COUNT << " " << FRAME_COUNT << " " << POPULATION_COUNT << std::endl;
}