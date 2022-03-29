#include "Strategy.h"

Strategy::Strategy(std::vector<int> r) {
    requests = r;
    hits = 0;
    misses = 0;
}

Strategy::~Strategy() {}