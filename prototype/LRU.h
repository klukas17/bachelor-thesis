#include "Strategy.h"

class LRU : public Strategy {
    public:
        virtual void simulate();

        LRU(std::vector<int> r);
        ~LRU();
};