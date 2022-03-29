#pragma once
#include <vector>

class Strategy {
    public:
        std::vector<int> requests;
        int hits;
        int misses;

        Strategy(std::vector<int> r);
        ~Strategy();
        virtual void simulate() = 0;
};