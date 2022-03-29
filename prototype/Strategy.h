#pragma once
#include <vector>
#include <map>

class Strategy {
    public:
        std::vector<int> requests;
        int page_count;
        int frame_count;
        int hits;
        int misses;
        std::map<int, int> page_to_frame;
        std::map<int, int> frame_to_page;
        int first_free_frame;

        Strategy(std::vector<int> r, int p_c, int f_c);
        ~Strategy();
        virtual void simulate() = 0;
        virtual void allocate(int page_request) = 0;
};