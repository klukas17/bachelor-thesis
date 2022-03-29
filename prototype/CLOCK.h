#include "Strategy.h"

class CLOCK : public Strategy {
    public:
        virtual void simulate();

        CLOCK(std::vector<int> r);
        ~CLOCK();
};