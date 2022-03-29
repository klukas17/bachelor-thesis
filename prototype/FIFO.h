#include "Strategy.h"

class FIFO : public Strategy {
    public:
        virtual void simulate();

        FIFO(std::vector<int> r);
        ~FIFO();
};