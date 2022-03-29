#include "LRU.h"
#include <iostream>

LRU::LRU(std::vector<int> r, int p_c, int f_c) : Strategy(r, p_c, f_c) {}
LRU::~LRU() {}

void LRU::simulate() {
    for (int r : requests)
        allocate(r);
}

void LRU::allocate(int page_request) {
    
}