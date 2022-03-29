#include "CLOCK.h"
#include <iostream>

CLOCK::CLOCK(std::vector<int> r, int p_c, int f_c) : Strategy(r, p_c, f_c) {}
CLOCK::~CLOCK() {}

void CLOCK::simulate() {
    for (int r : requests)
        allocate(r);
}

void CLOCK::allocate(int page_request) {
    
}