#include "Strategy.h"

class LFU : public Strategy {
    public:
        std::map<int, int> page_access_count;

        LFU(std::vector<int> r, int p_c, int f_c);
        ~LFU();

        virtual void simulate();
        virtual void allocate(int page_request);
};