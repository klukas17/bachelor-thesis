#include "OPT.h"
#include <iostream>

OPT::OPT(std::vector<int> r, int p_c, int f_c) : Strategy(r, p_c, f_c) {}
OPT::~OPT() {}

void OPT::simulate() {
    for (int r : requests)
        allocate(r);
}

void OPT::allocate(int page_request) {
    
}