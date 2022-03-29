#include "Strategy.h"
#include <queue>

class FIFO : public Strategy {
    public:
        std::queue<int> FIFO_queue;

        FIFO(std::vector<int> r, int p_c, int f_c);
        ~FIFO();

        virtual void simulate();
        virtual void allocate(int page_request);
};