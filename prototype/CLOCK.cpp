#include "CLOCK.h"

CLOCK::CLOCK(std::vector<int> r, int p_c, int f_c) : Strategy(r, p_c, f_c) {
    curr = 0;
    for (int i = 0; i < frame_count; i++) {
        info[i] = false;
    }
}
CLOCK::~CLOCK() {}

void CLOCK::simulate() {
    for (int r : requests)
        allocate(r);
}

void CLOCK::allocate(int page_request) {
    if (page_to_frame[page_request] != -1) {
        hits++;
        info[page_to_frame[page_request]] = true;
    }
    else {
        misses++;
        if (first_free_frame != -1) {
            frame_to_page[first_free_frame] = page_request;
            page_to_frame[page_request] = first_free_frame;

            info[first_free_frame] = true;

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
            while (frame == -1) {
                if (info[curr] == false) {
                    frame = curr;
                }
                else {
                    info[curr] = false;
                    curr++;
                    curr %= frame_count;
                }
            }
            info[frame] = true;
            // ********************************
            page_to_frame[frame_to_page[frame]] = -1;
            frame_to_page[frame] = page_request;
            page_to_frame[page_request] = frame;
        }
    }
}