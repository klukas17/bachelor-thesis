#include "LRU.h"
#include <climits>

LRU::LRU(std::vector<int> r, int p_c, int f_c) : Strategy(r, p_c, f_c) {
    for (int i = 0; i < frame_count; i++) {
        frame_last_time_accessed[i] = -1;
        request_index = 0;
    }
}
LRU::~LRU() {}

void LRU::simulate() {
    for (int r : requests)
        allocate(r);
}

void LRU::allocate(int page_request) {
    if (page_to_frame[page_request] != -1) {
        hits++;
        frame_last_time_accessed[page_to_frame[page_request]] = request_index;
    }
    else {
        misses++;
        if (first_free_frame != -1) {
            frame_to_page[first_free_frame] = page_request;
            page_to_frame[page_request] = first_free_frame;

            frame_last_time_accessed[first_free_frame] = request_index;

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
            int frame = -1;
            // ********************************
            int accessed = INT_MAX;
            for (int i = 0; i < frame_count; i++) {
                if (frame_last_time_accessed[i] < accessed) {
                    frame = i;
                    accessed = frame_last_time_accessed[i];
                }
            }
            frame_last_time_accessed[frame] = request_index;
            // ********************************
            page_to_frame[frame_to_page[frame]] = -1;
            frame_to_page[frame] = page_request;
            page_to_frame[page_request] = frame;
        }
    }
    request_index++;
}