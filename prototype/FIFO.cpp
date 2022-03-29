#include "FIFO.h"
#include <iostream>

FIFO::FIFO(std::vector<int> r) : Strategy(r) {}
FIFO::~FIFO() {}

void FIFO::simulate() {
    std::cout << "FIFO" << std::endl;
}