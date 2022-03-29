#include "Strategy.h"

class OPT : public Strategy {
    public:
        virtual void simulate();

        OPT(std::vector<int> r);
        ~OPT();
};