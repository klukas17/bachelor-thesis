#include "Strategy.h"
#include <map>

class GEStrategy : public Strategy {
    public:
        int strategy_index;
        int num1;
        int num2;
        int num3;
        int max_while_loop_iterations;
        int time;
        int cache_size;
        std::map<int, int> info1;
        std::map<int, int> info2;

        GEStrategy(std::vector<int> r, int p_c, int f_c, int s_i, int c_s);
        ~GEStrategy();

        virtual void simulate();
        virtual void allocate(int page_request);

        int find_min(int index);
        int find_max(int index);
        int division(int a, int b);
        int remainder(int a, int b);
        void write(int field, int index, int value);
        int read(int field, int index);
};