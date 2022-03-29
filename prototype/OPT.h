#include "Strategy.h"

class OPT : public Strategy {
    public:
        int current_request;

        OPT(std::vector<int> r, int p_c, int f_c);
        ~OPT();

        virtual void simulate();
        virtual void allocate(int page_request);
};