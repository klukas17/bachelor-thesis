#include "Strategy.h"
#include "FIFO.h"
#include "LRU.h"
#include "LFU.h"
#include "CLOCK.h"
#include "OPT.h"
#include "string"
#include "vector"
#include <fstream>
#include <sstream>
#include <iostream>

int main(int argc, char* argv[]) {
    std::string requests_path = argv[1];
    int page_count = std::stoi(argv[2]);
    int frame_count = std::stoi(argv[3]);

    std::vector<int> requests;
    std::ifstream in(requests_path);
    std::string line, segment;

    while (getline(in, line)) {
        std::stringstream s(line);
        while (getline(s, segment, ' ')) {
            requests.push_back(stoi(segment));
        }
    }

    Strategy* s1 = new FIFO(requests, page_count, frame_count);
    s1->simulate();
    std::cout << "FIFO: " << s1->hits << std::endl;

    Strategy* s2 = new LRU(requests, page_count, frame_count);
    s2->simulate();
    std::cout << "LRU: " << s2->hits << std::endl;

    Strategy* s3 = new LFU(requests, page_count, frame_count);
    s3->simulate();
    std::cout << "LFU: " << s3->hits << std::endl;

    Strategy* s4 = new CLOCK(requests, page_count, frame_count);
    s4->simulate();
    std::cout << "CLOCK: " << s4->hits << std::endl;

    Strategy* s5 = new OPT(requests, page_count, frame_count);
    s5->simulate();
    std::cout << "OPT: " << s5->hits << std::endl;  
}