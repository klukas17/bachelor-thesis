#include "Strategy.h"

Strategy::Strategy(std::vector<int> r, int p_c, int f_c) {
    requests = r;
    page_count = p_c;
    frame_count = f_c;
    hits = 0;
    misses = 0;
    first_free_frame = 0;
    for (int i = 0; i < page_count; i++) {
        page_to_frame[i] = -1;
    }
    for (int i = 0; i < frame_count; i++) {
        frame_to_page[i] = -1;
    }
}

Strategy::~Strategy() {}