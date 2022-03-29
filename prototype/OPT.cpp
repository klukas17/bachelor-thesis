#include "OPT.h"

OPT::OPT(std::vector<int> r, int p_c, int f_c) : Strategy(r, p_c, f_c) {
    current_request = 0;
}
OPT::~OPT() {}

void OPT::simulate() {
    for (int r : requests) {
        allocate(r);
        current_request++;
    }
}

void OPT::allocate(int page_request) {
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

            int frame = -1;
            int found_count = 0;
            int curr = current_request + 1;
            int frame_to_kick = -1;
            std::map<int, int> is_found;

            while (found_count < frame_count && curr < requests.size()) {
                int current_request = requests[curr];

                if (page_to_frame[current_request] == -1) {
                    curr++;
                }

                else {
                    if (!is_found[page_to_frame[current_request]]) {
                        is_found[page_to_frame[current_request]] = true;
                        frame_to_kick = page_to_frame[current_request];
                        found_count++;
                    }

                    curr++;
                }
            }

            if (found_count == frame_count) {
                frame = frame_to_kick;
            }
            else {
                for (int i = 0; i < frame_count; i++) {
                    if (!is_found[i]) {
                        frame = i;
                        break;
                    }
                }
            }

            page_to_frame[frame_to_page[frame]] = -1;
            frame_to_page[frame] = page_request;
            page_to_frame[page_request] = frame;

        }
    }
}