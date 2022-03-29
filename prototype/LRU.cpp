#include "LRU.h"
#include <iostream>

LRU::LRU(std::vector<int> r) : Strategy(r) {}
LRU::~LRU() {}

void LRU::simulate() {
    std::cout << "LRU" << std::endl;
}