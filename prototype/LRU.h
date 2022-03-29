#include "Strategy.h"

class LRU : public Strategy {
    public:
        LRU(std::vector<int> r, int p_c, int f_c);
        ~LRU();

        virtual void simulate();
        virtual void allocate(int page_request);
};