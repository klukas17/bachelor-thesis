#include "Strategy.h"
#include "GEStrategy.h"
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

    Strategy* s = new GEStrategy(requests, page_count, frame_count, 0, frame_count);
    s->simulate();
    std::cout << "GENERATED STRATEGY: " << s->hits << std::endl;
}