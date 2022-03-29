#include "FIFO.h"
#include <iostream>

FIFO::FIFO(std::vector<int> r, int p_c, int f_c) : Strategy(r, p_c, f_c) {}
FIFO::~FIFO() {}

void FIFO::simulate() {
    for (int r : requests)
        allocate(r);
}

void FIFO::allocate(int page_request) {
    if (page_to_frame[page_request] != -1) {
        hits++;
        std::cout << "HIT " << page_request << " HC=" << hits << std::endl;
    }
    else {
        misses++;
        if (first_free_frame != -1) {
            frame_to_page[first_free_frame] = page_request;
            page_to_frame[page_request] = first_free_frame;
            FIFO_queue.push(first_free_frame);

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
            int frame = FIFO_queue.front();
            FIFO_queue.pop();
            page_to_frame[frame_to_page[frame]] = -1;
            frame_to_page[frame] = page_request;
            page_to_frame[page_request] = frame;
            FIFO_queue.push(frame);
        }
        std::cout << "MISS " << page_request << " MC=" << misses << std::endl;
    }
    std::cout << "PAGE_TO_FRAME: ";
    for (const auto &p : page_to_frame)
        std::cout << p.first << "->" << p.second << " ";
    std::cout << std::endl;
    std::cout << "FRAME_TO_PAGE: ";
    for (const auto &p : frame_to_page)
        std::cout << p.first << "->" << p.second << " ";
    std::cout << std::endl;
}