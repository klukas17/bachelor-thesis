#include "LFU.h"
#include <iostream>
#include <climits>

LFU::LFU(std::vector<int> r, int p_c, int f_c) : Strategy(r, p_c, f_c) {
    for (int i = 0; i < page_count; i++) {
        page_access_count[i] = 0;
    
    }
}
LFU::~LFU() {}

void LFU::simulate() {
    for (int r : requests)
        this->allocate(r);
}

void LFU::allocate(int page_request) {
    if (page_to_frame[page_request] != -1) {
        hits++;
        std::cout << "HIT " << page_request << " HC=" << hits << std::endl;
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
            int accessed = INT_MAX;
            for (auto &p : frame_to_page) {
                if (page_access_count[p.second] < accessed) {
                    frame = p.first;
                    accessed = page_access_count[p.second];
                }
            }
            page_to_frame[frame_to_page[frame]] = -1;
            frame_to_page[frame] = page_request;
            page_to_frame[page_request] = frame;
        }
        std::cout << "MISS " << page_request << " MC=" << misses << std::endl;

    }
    page_access_count[page_request]++;
    std::cout << "PAGE_TO_FRAME: ";
    for (const auto &p : page_to_frame)
        std::cout << p.second << " ";
    std::cout << std::endl;
    std::cout << "FRAME_TO_PAGE: ";
    for (const auto &p : frame_to_page)
        std::cout << p.first << "->" << p.second << " ";
    std::cout << std::endl;
    std::cout << "PAGE_ACCESS_COUNT: ";
    for (const auto &p : page_access_count)
        std::cout << p.second << " ";
    std::cout << std::endl;
}