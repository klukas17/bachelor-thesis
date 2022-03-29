#include "Strategy.h"
#include <map>

class LRU : public Strategy {
    public:
        std::map<int, int> frame_last_time_accessed;
        int request_index;

        LRU(std::vector<int> r, int p_c, int f_c);
        ~LRU();

        virtual void simulate();
        virtual void allocate(int page_request);
};