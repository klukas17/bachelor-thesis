#include "Strategy.h"
#include <map>

class CLOCK : public Strategy {
    public:
        int curr;
        std::map<int, bool> info;

        CLOCK(std::vector<int> r, int p_c, int f_c);
        ~CLOCK();

        virtual void simulate();
        virtual void allocate(int page_request);
};