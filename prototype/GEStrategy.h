#pragma once
#include "Strategy.h"
#include <map>

class GEStrategy : public Strategy {
    public:
        int strategy_index;
        int num1;
        int num2;
        int num3;
        int time;
        int page_request;
        int cache_size;
        std::map<int, int> info1;
        std::map<int, int> info2;
        std::map<int, int> page_access_count;
        std::map<int, int> last_accessed;
        std::map<int, int> added_to_cache;
        std::map<int, int> accessed;

        GEStrategy(std::vector<int> r, int p_c, int f_c, int s_i, int c_s);
        ~GEStrategy();

        virtual void simulate();
        virtual void allocate(int page_request);

        int find_min(int index);
        int find_max(int index);
        int page_access_count_min();
        int page_access_count_max();
        int last_accessed_min();
        int last_accessed_max();
        int added_to_cache_min();
        int added_to_cache_max();
        int get_accessed(int frame);
        void set_accessed(int frame, int value);
        int division(int a, int b);
        int remainder(int a, int b);
        void write(int field, int index, int value);
        int read(int field, int index);
};