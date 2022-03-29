#include "CLOCK.h"
#include <iostream>

CLOCK::CLOCK(std::vector<int> r) : Strategy(r) {}
CLOCK::~CLOCK() {}

void CLOCK::simulate() {
    std::cout << "CLOCK" << std::endl;
}