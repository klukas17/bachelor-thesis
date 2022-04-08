#include "GEStrategy.h"
#include "GeneratedStrategies.h"
#include <climits>

GEStrategy::GEStrategy(std::vector<int> r, int p_c, int f_c, int s_i, int c_s) : Strategy(r, p_c, f_c) {
    strategy_index = s_i;
    cache_size = c_s;
    num1 = 0;
    num2 = 0;
    num3 = 0;
    time = 0;
    max_while_loop_iterations = 10000;
    for (int i = 0; i < frame_count; i++) {
        info1[i] = 0;
        info2[i] = 0;
    }
}
GEStrategy::~GEStrategy() {}

void GEStrategy::simulate() {
    for (int r : requests) {
        allocate(r);
        time++;
    }
}

int GEStrategy::find_min(int index) {
    std::map<int, int> m;
    if (index == 1) m = info1;
    if (index == 2) m = info2;
    int ret = -1;
    int val = INT_MAX;
    for (auto &pair : m)
        if (pair.second < val)
            ret = pair.first;
    return ret;
}

int GEStrategy::find_max(int index) {
    std::map<int, int> m;
    if (index == 1) m = info1;
    if (index == 2) m = info2;
    int ret = -1;
    int val = INT_MIN;
    for (auto &pair : m)
        if (pair.second > val)
            ret = pair.first;
    return ret;
}

int GEStrategy::division(int a, int b) {
    if (b != 0) return a / b;
    else return 1;
}

int GEStrategy::remainder(int a, int b) {
    if (b != 0) return a % b;
    else return 1;
}

void GEStrategy::write(int field, int index, int value) {
    if (field == 1 && index > 0 && index < cache_size) info1[index] = value;
    if (field == 2 && index > 0 && index < cache_size) info2[index] = value;
}

int GEStrategy::read(int field, int index) {
    if (field == 1 && index > 0 && index < cache_size) return info1[index];
    if (field == 2 && index > 0 && index < cache_size) return info2[index];
    return 0;
}

void GEStrategy::allocate(int page_request) {
    if (page_to_frame[page_request] != -1) {
        hits++;
    }
    else {
        misses++;
        if (first_free_frame != -1) {
            frame_to_page[first_free_frame] = page_request;
            page_to_frame[page_request] = first_free_frame;

            bool found = false;
            for (int i = first_free_frame; i < frame_count; i++) {
                if (frame_to_page[i] == -1) {
                    first_free_frame = i;
                    found = true;
                    break;
                }
            }
            if (!found)
                first_free_frame = -1;
        }
        else {
            int frame = GeneratedStrategies::function_1(this);
            page_to_frame[frame_to_page[frame]] = -1;
            frame_to_page[frame] = page_request;
            page_to_frame[page_request] = frame;
        }
    }
    GeneratedStrategies::function_2(this);
}