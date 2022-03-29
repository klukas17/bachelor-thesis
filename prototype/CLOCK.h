#include "Strategy.h"

class CLOCK : public Strategy {
    public:
        CLOCK(std::vector<int> r, int p_c, int f_c);
        ~CLOCK();

        virtual void simulate();
        virtual void allocate(int page_request);
};