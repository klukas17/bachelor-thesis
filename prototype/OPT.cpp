#include "OPT.h"
#include <iostream>

OPT::OPT(std::vector<int> r) : Strategy(r) {}
OPT::~OPT() {}

void OPT::simulate() {
    std::cout << "OPT" << std::endl;
}